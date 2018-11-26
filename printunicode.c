/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printunicode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:58:16 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/25 14:58:17 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	numbytes(int bits)
{
	int bytes;

	bytes = 1;
	(bits > 7) ? bytes = 2 : 0;
	(bits > 11) ? bytes = 3 : 0;
	(bits > 16) ? bytes = 4 : 0;
	return (bytes);
}

static int	len_bytes(void *s)
{
	wchar_t	*str;
	int		len;

	str = s;
	len = 0;
	while (*str)
	{
		len += numbytes(active_bits(*str));
		str++;
	}
	return (len);
}

int			put_un_ch(t_mask *mask, void *s)
{
	int		n;
	int		len;

	n = 0;
	if (MB_CUR_MAX == 1 && (wchar_t)s > 255)
		return (-1);
	len = (s) ? numbytes(active_bits((wchar_t)s)) : 1;
	(mask->minus == 0) ? n += ft_space_null(mask->width - len, mask) : 0;
	(s) ? n += print_unicode((wchar_t)s) : 0;
	(!s) ? n += write(1, &s, 1) : 0;
	(mask->minus == 1) ? n += ft_space_null(mask->width - len, mask) : 0;
	return (n);
}

int			put_un_string(t_mask *mask, void *s)
{
	int		count;
	int		acc;
	int		len;
	wchar_t	*str;

	acc = 0;
	str = s;
	count = nill(mask, s);
	NILL(count);
	if (MB_CUR_MAX == 1 && (wchar_t)s > 255)
		return (-1);
	len = (len_bytes(str) > mask->accurancy && mask->accurancy != -1) ?
			mask->accurancy : len_bytes(str);
	if (mask->minus == 0)
		count += ft_space_null(mask->width - len, mask);
	while (*str && acc < len)
	{
		acc += print_unicode(*str);
		str++;
	}
	count += acc;
	if (mask->minus == 1)
		count += ft_space_null(mask->width - len, mask);
	return (count + 1);
}
