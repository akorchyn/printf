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

static t_mask		*new_t_mask(void)
{
	t_mask		*new;

	if (!(new = (t_mask *)malloc(sizeof(t_mask))))
		return (NULL);
	new->type = BAD_TYPE;
	new->h = 0;
	new->hh = 0;
	new->l = 0;
	new->ll = 0;
	new->l_big = 0;
	new->null = 0;
	new->space = 0;
	new->plus = 0;
	new->minus = 0;
	new->sharp = 0;
	new->width = 0;
	new->accurancy = -1;
	return (new);
}

static void			flags(t_mask *mask, char *str, int *i)
{
	while (str[*i] != 'c' && str[*i] != 's' && str[*i] != 'p' && str[*i] != 'd'
		&& str[*i] != 'i' && str[*i] != 'x' && str[*i] != 'X' && str[*i] != 'o'
		&& str[*i] != 'f' && str[*i] != '%' && str[*i] != '.' && str[*i] != 'u'
		&& (str[*i] < '1' || str[*i] > '9') && str[*i]
		&& str[*i] != 'l' && str[*i] != 'h' && str[*i] != 'L' && str[*i] != '\\'
		&& str[*i] != '\"' && str[*i] != '\?'
		&& (str[*i] < 7 || str[*i] > 13))
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
	if (str[*i] == 'h')
	{
		*i = *i + 1;
		mask->h = (str[*i] == 'h') ? 0 : 1;
		mask->hh = (str[*i] == 'h') ? 1 : 0;
		(str[*i] == 'h') ? *i = *i + 1 : 0;
	}
	else if (str[*i] == 'l')
	{
		*i = *i + 1;
		mask->l = (str[*i] == 'l') ? 0 : 1;
		mask->ll = (str[*i] == 'l') ? 1 : 0;
		(str[*i] == 'h') ? *i = *i + 1 : 0;
	}
	else if (str[*i] == 'L')
	{
		mask->l_big = 1;
		*i = *i + 1;
	}
}

static void			type(t_mask *mask, char *str, int *i)
{
	(str[*i] == 'c') ? mask->type = CHAR : 0;
	(str[*i] == 's') ? mask->type = STRING : 0;
	(str[*i] == 'p') ? mask->type = POINTER : 0;
	(str[*i] == 'd') ? mask->type = DECIMAL : 0;
	(str[*i] == 'i') ? mask->type = INT : 0;
	(str[*i] == 'o') ? mask->type = U_OCTAL : 0;
	(str[*i] == 'u') ? mask->type = U_DECIMAL : 0;
	(str[*i] == 'x') ? mask->type = U_HEX_LOWER : 0;
	(str[*i] == 'X') ? mask->type = U_HEX_UPPER : 0;
	(str[*i] == 'f') ? mask->type = FLOAT : 0;
	(str[*i] == '%') ? mask->type = PERCENT : 0;
	(mask->type != BAD_TYPE) ? *i = *i + 1 : 0;
}

int					read_mask(char *str, t_mask **mask)
{
	int			i;

	i = 1;
	if (!(*mask = new_t_mask()))
		return (0);
	flags(*mask, str, &i);
	if ((ft_isdigit(str[i])))
		(*mask)->width = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
	{
		((*mask)->accurancy) = ft_atoi(str + i + 1);
		i++;
		while (ft_isdigit(str[i]))
			i++;
	}
	size(*mask, str, &i);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd'
		&& str[i] != 'i' && str[i] != 'x' && str[i] != 'X' && str[i] != 'o'
		&& str[i] != 'f' && str[i] != '%' && str[i] != 'u' && str[i] != '\\'
		&& (str[i] < 7 || str[i] > 13) && str[i] != '\"' && str[i])
		i++;
	type(*mask, str, &i);
	return (i);
}
