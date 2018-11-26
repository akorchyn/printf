/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:05:49 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/15 17:15:09 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			check(char c)
{
	return (c != 'c' && c != 's' && c != 'p' && c != 'd' && c != 'x'
			&& c != 'X' && c != 'o' && c != 'f' && c != '%' && c != 'u'
			&& c != 'F' && c != 'i' && (c < 7 || c > 13) && c != 'U' && c
			&& c != 'D' && c != 'O' && c != 63 && c != 92 && c != 'C'
			&& c != 'S' && c != 34 && c != 'b' && c != 'm');
}

static void			flags(t_mask *mask, char *str, int *i)
{
	while ((str[*i] < '1' || str[*i] > '9') && str[*i] && str[*i] != 'j'
		&& str[*i] != 'l' && str[*i] != 'h' && str[*i] != 'L' && str[*i] != 'z'
		&& str[*i] != '.' && str[*i] != '*' && check(str[*i]))
	{
		(str[*i] == '0') ? mask->null = 1 : 0;
		(str[*i] == '+') ? mask->plus = 1 : 0;
		(str[*i] == '-') ? mask->minus = 1 : 0;
		(str[*i] == '#') ? mask->sharp = 1 : 0;
		(str[*i] == ' ') ? mask->space = 1 : 0;
		(*i)++;
	}
	(mask->minus == 1) ? mask->null = 0 : 0;
	(mask->plus == 1) ? mask->space = 0 : 0;
}

static void			size(t_mask *mask, char *str, int *i)
{
	(str[*i] == 'j') ? mask->j = 1 : 0;
	(str[*i] == 'z') ? mask->z = 1 : 0;
	(str[*i] == 'L') ? mask->l_big = 1 : 0;
	if (str[*i] == 'h')
	{
		*i = *i + 1;
		mask->h = (str[*i] == 'h') ? 0 : 1;
		mask->hh = (str[*i] == 'h') ? 1 : 0;
	}
	else if (str[*i] == 'l')
	{
		*i = *i + 1;
		mask->l = (str[*i] == 'l') ? 0 : 1;
		mask->ll = (str[*i] == 'l') ? 1 : 0;
	}
	(str[*i] == 'l') ? (*i)++ : 0;
	(str[*i] == 'L') ? (*i)++ : 0;
	(str[*i] == 'j') ? (*i)++ : 0;
	(str[*i] == 'z') ? (*i)++ : 0;
	(str[*i] == 'h') ? (*i)++ : 0;
}

static void			type(t_mask *mask, char *str, int *i)
{
	(str[*i] == 'c') ? mask->type = CHAR : 0;
	(str[*i] == 'C') ? mask->type = UNICODE_CH : 0;
	(str[*i] == 'S') ? mask->type = UNICODE_STR : 0;
	(str[*i] == 's') ? mask->type = STRING : 0;
	(str[*i] == 'p') ? mask->type = POINTER : 0;
	(str[*i] == 'd' || str[*i] == 'D' || str[*i] == 'i')
	? mask->type = DECIMAL : 0;
	(str[*i] == 'D') ? mask->l = 1 : 0;
	(str[*i] == 'o' || str[*i] == 'O') ? mask->type = U_OCTAL : 0;
	(str[*i] == 'O') ? mask->l = 1 : 0;
	(str[*i] == 'u' || str[*i] == 'U') ? mask->type = U_DECIMAL : 0;
	(str[*i] == 'U') ? mask->l = 1 : 0;
	(str[*i] == 'x') ? mask->type = U_HEX_LOWER : 0;
	(str[*i] == 'X') ? mask->type = U_HEX_UPPER : 0;
	(str[*i] == 'f' || str[*i] == 'F') ? mask->type = FLOAT : 0;
	(str[*i] == '%') ? mask->type = PERCENT : 0;
	(str[*i] == 'b') ? mask->type = BINARY : 0;
	(str[*i] == 'm') ? mask->type = MEMORY : 0;
	(mask->type != BAD_TYPE) ? *i = *i + 1 : 0;
}

int					read_mask(char *str, t_mask **mask, va_list *ap)
{
	int			i;

	i = 1;
	if (!(*mask = new_t_mask()))
		return (0);
	flags(*mask, str, &i);
	(str[i] == '*') ? (*mask)->width = va_arg(*ap, int) : 0;
	(str[i] == '*') ? i++ : 0;
	(ft_isdigit(str[i]) == 1) ? (*mask)->width = ft_atoi(str + i) : 0;
	while (ft_isdigit(str[i]))
		i++;
	(str[i] == '*') ? (*mask)->width = va_arg(*ap, int) : 0;
	(str[i] == '*') ? i++ : 0;
	if (str[i] == '.')
	{
		((*mask)->accurancy) = (str[++i] != '*') ? ft_atoi(str + i)
				: va_arg(*ap, int);
		while (ft_isdigit(str[i]))
			i++;
	}
	size(*mask, str, &i);
	while (check(str[i]))
		i++;
	type(*mask, str, &i);
	return (i);
}
