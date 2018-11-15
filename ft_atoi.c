/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:42:00 by akorchyn          #+#    #+#             */
/*   Updated: 2018/10/27 20:18:14 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ad_op(char *str, int *i)
{
	int	sign;

	sign = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		*i = *i + 1;
	if (str[*i] == '-')
		sign = -1;
	if (str[*i] == '-' || str[*i] == '+')
		*i = *i + 1;
	return (sign);
}

int				ft_atoi(const char *s)
{
	int					sign;
	unsigned long int	res;
	int					i;
	char				*str;

	str = (char *)s;
	i = 0;
	res = 0;
	sign = ad_op(str, &i);
	while (ft_isdigit(str[i]))
	{
		if ((res >= 922337203685477580 || (res == 922337203685477580 &&
					(str[i] - '0') > 7)) && sign == 1)
			return (-1);
		if ((res >= 922337203685477580 || (res == 922337203685477580 &&
					(str[i] - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
	return ((int)(sign * res));
}
