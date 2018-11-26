/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:18:21 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/22 16:20:15 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_space_null(int n, t_mask *mask)
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

int		print_zero(int n)
{
	int count;

	count = 0;
	while (n-- > 0)
		count += write(1, "0", 1);
	return (count);
}

t_mask	*new_t_mask(void)
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
	new->j = 0;
	new->z = 0;
	new->plus = 0;
	new->minus = 0;
	new->sharp = 0;
	new->width = 0;
	new->accurancy = -1;
	return (new);
}

int		ft_space_null_di(int n, t_mask *mask)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		(mask->null == 0 || mask->accurancy > -1) ? write(1, " ", 1) : 0;
		if (mask->null == 1 && mask->accurancy == -1)
			write(1, "0", 1);
		n--;
		i++;
	}
	return (i);
}

int		u_null(t_mask *mask, void *data)
{
	if ((unsigned long long)data == 0 && mask->accurancy == 0)
	{
		if (mask->sharp == 1 && mask->type == U_OCTAL && mask->width > -1)
		{
			write(1, "0", 1);
			mask->width--;
			return (1);
		}
		if ((mask->type == POINTER || (mask->type == BINARY && mask->sharp))
		&& mask->width > -1)
		{
			(mask->type == POINTER) ? write(1, "0x", 2) : write(1, "0b", 2);
			mask->width -= 2;
			return (2);
		}
		return (0);
	}
	return (-1);
}
