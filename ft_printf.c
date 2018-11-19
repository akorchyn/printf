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
#include <stdio.h>

int			ft_space_null(int n, t_mask *mask)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		(mask->null == 0) ? write(1, " ", 1) : 0;
		(mask->null == 1) ? write(1, "0", 1) : 0;
		n--;
		i++;
	}
	return (i);
}

int			bad_type(t_mask *mask, void *s)
{
	if (!s)
		ft_space_null(mask->width, mask);
	return ((mask->width > 0) ? mask->width - 1 : 0);
}

int		percent(t_mask *mask, void *data)
{
	if (!data)
		return (ft_putch(mask, (void *)'%'));
	return (0);	
}

t_functions	*update(void)
{
	t_functions	*funcs;

	funcs = (t_functions *)malloc(sizeof(t_functions) * 13);
	funcs[CHAR] = ft_putch;
	funcs[STRING] = ft_putstring;
	funcs[BAD_TYPE] = bad_type;
	funcs[POINTER] = pointer;
	funcs[PERCENT] = percent;
	funcs[DECIMAL] = decimal;
	funcs[INT] = decimal;
	funcs[U_OCTAL] = octal;
	funcs[U_DECIMAL] = unsigned_decimal;
	funcs[U_HEX_LOWER] = hexdecimal_low;
	funcs[U_HEX_UPPER] = hexdecimal_up;
	return (funcs);
}

int			all_oper(t_mask *mask, void *data)
{
	t_functions	*funcs;
	int			len;

	len = 0;
	funcs = update();
	len += funcs[mask->type](mask, data);
	free(funcs);
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
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
			if (mask->type == BAD_TYPE || mask->type == PERCENT)
				len += all_oper(mask, NULL);
			else
				len += all_oper(mask, va_arg(ap, void *));
			free(mask);
			(i > 0) ? i-- : 0;
			continue ;
		}
		len += write(1, &(format[i]), 1);
	}
	va_end(ap);
	//system("leaks a.out");
	return (len);
}

// int	main(void)
// {	char	*b;
// 	long	x = 4294967296;
// 	printf("%s\n", ft_itoa_base(NULL, 16, 0));
// 	printf("%i\n", printf("% 4.5i", 42));
// 	fflush(stdout);
// 	printf("%i\n", ft_printf("% 4.5i", 42));
// }
