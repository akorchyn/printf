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

void		**update(void)
{
	void		**funcs;

	funcs = (void **)malloc(sizeof(void *) * 13);
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
	funcs[FLOAT] = print_float;
	return (funcs);
}

int			all_oper(t_mask *mask, va_list ap, void **funcs)
{
	int		(*func)(t_mask *, void *);
	int		(*floats)(t_mask *, long double, int);
	int		len;

	len = 0;
	(mask->width < -1) ? mask->width = 0 : 0;
	(mask->type != FLOAT) ? func = funcs[mask->type] : 0;
	(mask->type == FLOAT) ? floats = funcs[mask->type] : 0;
	if (mask->type == BAD_TYPE || mask->type == PERCENT)
		len += func(mask, NULL);
	else if (mask->type == FLOAT)
		len += (mask->l_big) ? floats(mask, va_arg(ap, long double), 0)
	: floats(mask, va_arg(ap, double), 0);
	else
		len += func(mask, va_arg(ap, void *));
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_mask		*mask;
	void		**funcs;
	int			i;
	int			len;

	i = -1;
	len = 0;
	funcs = update();
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += read_mask(((char *)format) + i, &mask);
			len += all_oper(mask, ap, funcs);
			free(mask);
			(i > 0) ? i-- : 0;
			continue ;
		}
		len += write(1, &(format[i]), 1);
	}
	va_end(ap);
	free(funcs);
	return (len);
}

//int	main(void)
//{	char	*b;
//	long	x = 4294967296;
//	printf("%i\n", printf("{% 03d}", 0));
//	fflush(stdout);
//	printf("%i\n", ft_printf("{% 03d}", 0));
//}
