/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:14:14 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/14 14:14:16 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		translate(int n, int let_case)
{
	if (n < 10)
		return (n + '0');
	else if (n >= 10 && let_case == 0)
		return ('a' + (n - 10));
	else
		return ('A' + (n - 10));
}

char			*ibase(__uint128_t nb, int base, int let_case)
{
	char			*str;
	char			*start;
	__uint128_t		tmp;
	int				nblen;

	nblen = (!nb) ? 1 : 0;
	tmp = nb;
	while (tmp > 0)
	{
		tmp /= base;
		nblen++;
	}
	str = malloc(sizeof(char) * (nblen + 1));
	start = str;
	while (nblen-- > 0)
	{
		*str = translate(nb % base, let_case);
		str++;
		nb = nb / base;
	}
	*str = '\0';
	ft_strrev(start);
	return (start);
}
