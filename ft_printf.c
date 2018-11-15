/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:52:03 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/13 11:52:05 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>
#include <stdio.h>

int			ft_putch(t_mask *mask, int c)
{
	char	to_add;
	int		len;

	to_add = ' ';
	len = 0;
	(mask->null == 1) ? to_add = '0' : 0;
	while ((mask->width)-- > 1 && mask->minus == 0)
	{
		write(1, &to_add, 1);
		len++;
	}
	write(1, &c, 1);
	while ((mask->width)-- > 0 && mask->minus == 1)
	{
		len++;
		write(1, " ", 1);
	}
	return (len + 1);
}

int			ft_putstr(t_mask *mask, char *str)
{
	char	to_add;
	int		len;
	int		len_str;
	int		i;

	to_add = ' ';
	len = 0;
	i = -1;
	len_str = ft_strlen(str);
	(mask->null == 1) ? to_add = '0' : 0;
	while (mask->width > len_str && mask->minus == 0)
	{
		write(1, &to_add, 1);
		mask->width--;
		len++;
	}
	write(1, str, len_str);
	while (mask->width > len_str && mask->minus == 1)
	{
		write(1, " ", 1);
		mask->width--;
		len++;
	}
	return (len_str + len);
}

int			ft_printf(const char *format, ...)
{
	va_list 	ap;
	t_mask		*mask;
	int			i;
	int			len;

	i = -1;
	len = 0;
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += read_mask(((char *)format) + i, &mask);
			(mask->type == CHAR && mask->l == 0) ? len += ft_putch(mask, va_arg(ap, unsigned char)) : 0;
			(mask->type == CHAR && mask->l == 1) ? len += ft_putch(mask, va_arg(ap, wchar_t)) : 0;
			(mask->type == STRING && mask->l == 0) ? len += ft_putstr(mask, va_arg(ap, char *)) : 0;
			(mask->type == STRING && mask->l == 1) ? len += ft_putstr(mask, va_arg(ap, wchar_t *)) : 0;
			(mask->type == BAD_TYPE) ? write(1, "%", 1) : 0;
			free(mask);
			i--;
			continue ;
		}
		write(1, &(format[i]), 1);
		len++;
	}
	va_end(ap);
	return (len);
}

// int main()
// {
// 	printf("%010s\n", "abcde");
// 	ft_printf("%010s\n", "abcde");
// }