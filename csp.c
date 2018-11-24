/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:48:21 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/13 16:57:41 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nill(t_mask *mask, void *data)
{
	int		len;
	int		k;

	len = 0;
	if (!data)
	{
		k = (mask->accurancy > -1) ? mask->accurancy : 6;
		len += ft_space_null(mask->width - k, mask);
		len += write(1, "(null)", (mask->accurancy > -1) ? mask->accurancy : 6);
		return (len);
	}
	return (0);
}

int			pointer(t_mask *mask, void *data)
{
	char			*str;
	int				len;
	int				count;

	count = u_null(mask, data);
	CHECK(count);
	str = ibase((unsigned long long)data, 16, 0);
	len = ft_strlen(str);
	if (mask->minus == 0 && mask->null == 0)
		count += ft_space_null(mask->width - len - 2, mask);
	count += write(1, "0x", 2);
	if (mask->minus == 0 && mask->null == 1)
		count += ft_space_null(mask->width - len - 2, mask);
	while (mask->accurancy-- > len)
		count += write(1, "0", 1);
	count += write(1, str, len);
	if (mask->minus == 1)
		count += ft_space_null(mask->width - len - 2, mask);
	free(str);
	return (count + 1);
}

int			ft_putch(t_mask *mask, void *s)
{
	int n;
	char c;

	n = 0;
	if (MB_CUR_MAX == 1 && (wchar_t)s > 255)
		return (-1);
	(mask->minus == 0) ? n += ft_space_null(mask->width - 1, mask) : 0;
	if (mask->l == 1 || mask->type == UNICODE_CH)
		n += print_unicode((wchar_t )s);
	else
	{
		c = (char) s;
		n += write(1, &s, 1);
	}
	(mask->minus == 1) ? n += ft_space_null(mask->width - 1, mask) : 0;
	return (n);
}

int			ft_putstring(t_mask *mask, void *s)
{
	int		count;
	int		len;

	if (MB_CUR_MAX == 1 && (wchar_t)s > 255)
		return (-1);
	count = nill(mask, s);
	NILL(count);
	len = (ft_strlen(s) > mask->accurancy && mask->accurancy != -1) ?
	mask->accurancy : ft_strlen(s);
	if (mask->minus == 0)
		count += ft_space_null(mask->width - len, mask);
	if (mask->l == 1 || mask->type == UNICODE_STR)
	{
		len = -1;
		while (((wchar_t *)s)[++len])
			if ((count += print_unicode(((wchar_t *)s)[len])) == -1)
				return (-1);
	}
	else
		count += write(1, s, len);
	if (mask->minus == 1)
		count += ft_space_null(mask->width - len, mask);
	return (count);
}
