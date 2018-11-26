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

unsigned long long			converter(t_mask *mask, void *data)
{
	if (mask->l == 1)
		return ((unsigned long)(data));
	else if (mask->ll == 1)
		return ((unsigned long long)data);
	else if (mask->h == 1)
		return ((unsigned short)data);
	else if (mask->hh == 1)
		return ((unsigned char)data);
	else if (mask->z == 1)
		return ((size_t)data);
	else if (mask->j == 1)
		return ((uintmax_t)data);
	return ((unsigned int)data);
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
	num = ibase(converter(mask, data), 8, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->sharp == 1 && nzeros > 0) ? nzeros-- : 0;
	(mask->sharp == 1 && nzeros == 0) ? nspaces-- : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0 || !mask->accurancy))
		n += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1 && num[0] != '0') ? n += write(1, "0", 1) : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0 && mask->accurancy)
		n += ft_space_null_di(nspaces, mask);
	n += print_zero(nzeros);
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
	num = ibase(converter(mask, data), 10, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->minus == 0) ? count += ft_space_null_di(nspaces, mask) : 0;
	count += print_zero(nzeros);
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
	num = ibase(converter(mask, data), 16, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->sharp == 1) ? nspaces -= 2 : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0 || !mask->accurancy))
		count += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1 && num[0] != '0') ? count += write(1, "0x", 2) : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0 && mask->accurancy)
		count += ft_space_null_di(nspaces, mask);
	count += print_zero(nzeros);
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
	num = ibase(converter(mask, data), 16, 1);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - len - nzeros : 0;
	(mask->sharp == 1) ? nspaces -= 2 : 0;
	if (mask->minus == 0 && (mask->null == 0 || nzeros > 0 || !mask->accurancy))
		count += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1 && num[0] != '0') ? count += write(1, "0X", 2) : 0;
	if (mask->minus == 0 && mask->null == 1 && nzeros == 0 && mask->accurancy)
		count += ft_space_null_di(nspaces, mask);
	count += print_zero(nzeros);
	count += write(1, num, len);
	(mask->minus == 1) ? count += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (count);
}
