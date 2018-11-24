/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:18:47 by akorchyn          #+#    #+#             */
/*   Updated: 2018/10/27 20:23:00 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*additional(__int128 un, __int128 n, int len_arr)
{
	char			*str;
	char			temp;
	int				i;
	int				j;

	str = (char *)malloc(len_arr);
	if (!str)
		return (NULL);
	i = 0;
	while (un > 0)
	{
		str[i++] = (un % 10) + '0';
		un = un / 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i--] = '\0';
	j = 0;
	while (j < i)
	{
		temp = str[i];
		str[i--] = str[j];
		str[j++] = temp;
	}
	return (str);
}

char		*ft_itoa(__int128 n)
{
	char				*ans;
	__int128			un;
	__int128			to_count;
	int					i;

	i = 1;
	if (n == 0)
	{
		ans = (char *)malloc(2);
		if (!ans)
			return (NULL);
		ans[0] = '0';
		ans[1] = '\0';
		return (ans);
	}
	un = (n > 0) ? n : -n;
	to_count = un;
	while (to_count > 0)
	{
		i++;
		to_count = to_count / 10;
	}
	if (n < 0)
		i++;
	return (additional(un, n, i));
}
