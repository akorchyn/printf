/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:02:18 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/17 18:02:19 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	converter(t_mask *mask, void *data)
{
	if (mask->l == 1)
		return ((unsigned long)(data));
	if (mask->ll == 1)
		return ((unsigned long long)data);
	if (mask->h == 1)
		return ((unsigned short)data);
	if (mask->hh == 1)
		return ((unsigned char)data);
	return ((unsigned int)data);
}

int							u_null(t_mask *mask, void *data)
{
	if ((unsigned long long)data == 0 && mask->accurancy == 0)
	{
		if (mask->sharp == 1 && mask->type == U_OCTAL && mask->width > -1)
		{
			write(1, "0", 1);
			mask->width--;
			return (1);
		}
		if (mask->type == POINTER && mask->width > -1)
		{
			write(1, "0x", 2);
			mask->width -= 2;
			return (2);
		}
		return (0);
	}
	return (-1);
}

int							octal(t_mask *mask, void *data)
{
	char	*num;
	int		len;
	int		n;
	int		nzeros;
	int		nspaces;

	n = (int)u_null(mask, data);
	CHECK(n);
	num = ft_itoa_base(converter(mask, data), 8, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->sharp == 1 && nzeros > 0) ? nzeros-- : 0;
	(mask->sharp == 1 && nzeros == 0) ? nspaces-- : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0))
		n += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1 && num[0] != '0') ? n += write(1, "0", 1) : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0)
		n += ft_space_null_di(nspaces, mask);
	while (nzeros-- > 0)
		n += write(1, "0", 1);
	(!(mask->accurancy == 0 && num[0] == '0')) ? n += write(1, num, len) : 0;
	(mask->minus == 1) ? n += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (n + 1);
}

int							unsigned_decimal(t_mask *mask, void *data)
{
	int		len;
	int		count;
	char	*num;
	int		nzeros;
	int		nspaces;

	len = (int)u_null(mask, data);
	CHECK(len);
	count = 0;
	num = ft_itoa_base(converter(mask, data), 10, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->minus == 0) ? count += ft_space_null_di(nspaces, mask) : 0;
	while (nzeros-- > 0)
		count += write(1, "0", 1);
	count += write(1, num, len);
	(mask->minus == 1) ? count += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (count);
}

int							hexdecimal_low(t_mask *mask, void *data)
{
	char	*num;
	int		len;
	int		count;
	int		nzeros;
	int		nspaces;

	len = (int)u_null(mask, data);
	CHECK(len);
	count = 0;
	num = ft_itoa_base(converter(mask, data), 16, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->sharp == 1) ? nspaces -= 2 : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0))
		count += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1 && num[0] != '0') ? count += write(1, "0x", 2) : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0)
		count += ft_space_null_di(nspaces, mask);
	while (nzeros-- > 0)
		count += write(1, "0", 1);
	count += write(1, num, len);
	(mask->minus == 1) ? count += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (count);
}

int							hexdecimal_up(t_mask *mask, void *data)
{
	char	*num;
	int		len;
	int		count;
	int		nzeros;
	int		nspaces;

	len = (int)u_null(mask, data);
	CHECK(len);
	count = 0;
	num = ft_itoa_base(converter(mask, data), 16, 1);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->sharp == 1) ? nspaces -= 2 : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0))
		count += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1 && num[0] != '0') ? count += write(1, "0X", 2) : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0)
		count += ft_space_null_di(nspaces, mask);
	while (nzeros-- > 0)
		count += write(1, "0", 1);
	count += write(1, num, len);
	(mask->minus == 1) ? count += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (count);
}
