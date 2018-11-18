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

static char	translate(int n, int let_case)
{
	if (n < 10)
		return (n + '0');
	else if (n >= 10 && let_case == 0)
		return ('a' + (n - 10));
	else
		return ('A' + (n - 10));
}

static char	*all_op(unsigned long long num, int len, int base, int let_case)
{
	char	*str;
	int		i;
	int		j;
	char	temp;

	j = 0;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	while (num > 0)
	{
		str[i++] = translate(num % base, let_case);
		num = num / base;
	}
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
	char					*str;
	int						len;
	unsigned long long		num;

	num = nb;
	len = 0;
	while (num > 0)
	{
		len++;
		num = num / base;
	}
	if (nb == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (base > 1 && base < 17 && nb > 0)
		str = all_op(nb, len, base, let_case);
	else
		return (NULL);
	return (str);
}
