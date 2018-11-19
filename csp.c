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

static int	ft_wlen(wchar_t *str)
{
	int		i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

static int	nill(t_mask *mask, void *data)
{
	if (!data)
	{
		write(1, "(null)", 6);
		mask->width -= 6;
		return (-1);
	}
	return (0);
}

int			pointer(t_mask *mask, void *data)
{
	char			*str;
	int				len;

	CHECK(u_null(mask, data));
	str = ft_itoa_base((unsigned long long)data, 16, 0);
	len = ft_strlen(str);
	if (mask->minus == 0 && mask->null == 0)
		ft_space_null(mask->width - len - 3, mask);
	write(1, "0x", 2);
	if (mask->minus == 0 && mask->null == 1)
		ft_space_null(mask->width - len - 3, mask);
	write(1, str, len);
	(mask->minus == 1) ? ft_space_null(mask->width - len - 3, mask) : 0;
	free(str);
	if (mask->width > len)
		return (mask->width);
	return (len);
}

int			ft_putch(t_mask *mask, void *s)
{
	char	c;
	wchar_t	wchar_c;

	(mask->minus == 0) ? ft_space_null(mask->width - 1, mask) : 0;
	if (mask->l == 0)
	{
		c = (char)s;
		write(1, &c, 1);
	}
	else
	{
		wchar_c = (wchar_t)s;
		write(1, &wchar_c, sizeof(wchar_t));
	}
	(mask->minus == 1) ? ft_space_null(mask->width - 1, mask) : 0;
	if (mask->width == 0)
		return (1);
	return (mask->width);
}

int			ft_putstring(t_mask *mask, void *s)
{
	int		count;
	int		len;

	count = 0;
	NILL(nill(mask, s));
	if (mask->l == 1)
	{
		len = (ft_wlen(s) > mask->accurancy && mask->accurancy != -1) ? mask->accurancy : ft_wlen(s);
		if (mask->minus == 0)
			count += ft_space_null(mask->width - len, mask);
		count += write(1, s, len);
		if (mask->minus == 1)
			count += ft_space_null(mask->width - len, mask);
	}
	else
	{
		len = (ft_strlen(s) > mask->accurancy && mask->accurancy != -1) ? mask->accurancy : ft_strlen(s);
		if (mask->minus == 0)
			count += ft_space_null(mask->width - len, mask);
		count += write(1, s, len);
		if (mask->minus == 1)
			count += ft_space_null(mask->width - len, mask);
	}
	return (count);
}
