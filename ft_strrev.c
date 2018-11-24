/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:43:05 by akorchyn          #+#    #+#             */
/*   Updated: 2018/10/27 17:36:19 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev(char *string)
{
	int		start;
	int		end;
	char	temp;

	end = ft_strlen(string) - 1;
	start = 0;
	while (start < end)
	{
		temp = string[end];
		string[end--] = string[start];
		string[start++] = temp;
	}
	return (string);
}
