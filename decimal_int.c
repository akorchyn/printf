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

int					ft_space_null_di(int n, t_mask *mask)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		(mask->null == 0 || mask->accurancy > -1) ? write(1, " ", 1) : 0;
		if (mask->null == 1 && mask->accurancy == -1)
			write(1, "0", 1);
		n--;
		i++;
	}
	return (i);
}

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
	else
		return ((int)data);
}

static int			null(t_mask *mask, void *data)
{
	if ((long long)data == 0 && mask->accurancy == 0)
		return (0);
	return (-1);
}

int					decimal(t_mask *mask, void *data)
{
	int			len;
	int			count;
	char		*num;
	int			nzeros;
	int			nspaces;

	count = null(mask, data);
	CHECK(count);
	num = ft_itoa(convert(mask, data));
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	(mask->accurancy > 0 && num[0] == '-') ? nzeros++ : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->space && num[0] != '-' && !nspaces) ? nspaces++ : 0;
	(mask->plus == 1 && num[0] != '-') ? nspaces-- : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0))
		count += ft_space_null_di(nspaces, mask);
	if (mask->plus == 1 && convert(mask, data) > -1)
		count += write(1, "+", 1);
	else if (mask->plus == 1 || num[0] == '-')
		count += write(1, "-", 1);
	(num[0] == '-') ? num++ : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0)
		count += ft_space_null_di(nspaces, mask);
	while (nzeros-- > 0)
		count += write(1, "0", 1);
	count += write(1, num, ft_strlen(num));
	(mask->minus == 1) ? count += ft_space_null_di(nspaces, mask) : 0;
	(ft_strlen(num) == len) ? free(num) : free(num - 1);
	return (count + 1);
}
