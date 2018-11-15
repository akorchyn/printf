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

static char	translate(int nb, int base, int let_case)
{
	int		n;

	n = nb % base;
	if (n < 10)
		return (n + '0');
	else if (n > 10 && let_case == 0)
		return ('a' + (n - 10));
	else
		return ('A' + (n - 10));
}

static char	*all_op(unsigned int num, int nb, int base, int let_case)
{
	char	*str;
	int		i;
	int		j;
	char	temp;

	j = 0;
	i = 0;
	str = malloc(sizeof(char) * 33);
	while (num > 0)
	{
		str[i++] = translate(num % base, base, let_case);
		num = num / base;
	}
	if (nb < 0 && base == 10)
		str[i++] = '-';
	str[i--] = '\0';
	while (j < i)
	{
		temp = str[j];
		str[j++] = str[i];
		str[i--] = temp;
	}
	return (str);
}

char		*ft_itoa_base(unsigned long long nb, int base, int let_case)
{
	char			*str;
	unsigned int	num;

	num = nb;
	if (nb == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (base > 1 && base < 17 && num > 0)
		str = all_op(num, nb, base, let_case);
	else
		return (NULL);
	return (str);
}
