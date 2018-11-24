/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioxX.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 12:33:11 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/17 12:33:13 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	convert(t_mask *mask, void *data)
{
	if (mask->l == 1)
		return ((long)data);
	else if (mask->ll == 1)
		return ((long long)data);
	else if (mask->h == 1)
		return ((short)data);
	else if (mask->hh == 1)
		return ((char)data);
	else if (mask->z == 1)
		return ((size_t)data);
	else if (mask->j == 1)
		return ((intmax_t)data);
	else
		return ((int)data);
}

static int			null(t_mask *mask, void *data)
{
	if ((long long)data == 0 && mask->accurancy == 0)
		return (0);
	return (-1);
}

static int			plus_minus(t_mask *mask, char *num)
{
	if (mask->plus && num[0] != '-')
		return ((int)write(1, "+", 1));
	if (num[0] == '-')
		return ((int)write(1, "-", 1));
	return (0);
}

static int			spacebeforenull(t_mask *mask, int nspaces)
{
	int count;

	count = 0;
	(mask->space) ? count += write(1, " ", 1) : 0;
	(mask->space) ? nspaces-- : 0;
	count += ft_space_null_di(nspaces, mask);
	return (count);
}

int					decimal(t_mask *mask, void *data)
{
	int			len;
	int			n;
	char		*num;
	int			nzeros;
	int			nspaces;

	n = null(mask, data);
	CHECK(n);
	num = ft_itoa(convert(mask, data));
	len = (num[0] == '-') ? ft_strlen(num) - 1 : ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(!nspaces && mask->space) ? nspaces++ : 0;
	(mask->plus && num[0] != '-') ? nspaces-- : 0;
	(num[0] == '-') ? nspaces-- : 0;
	if ((!mask->null || nzeros) && !mask->minus)
		n += ft_space_null_di(nspaces, mask);
	n += plus_minus(mask, num);
	if (mask->null && !nzeros && !mask->minus)
		n += spacebeforenull(mask, nspaces);
	n += print_zero(nzeros);
	n += (num[0] == '-') ? write(1, num + 1, len) : write(1, num, len);
	(mask->minus) ? n += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (n + 1);
}
