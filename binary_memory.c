/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:17:35 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/25 17:17:37 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				print_binary(t_mask *mask, void *data)
{
	int		n;
	int		len;
	char	*num;
	int		nzeros;
	int		nspaces;

	n = u_null(mask, data);
	CHECK(n);
	num = ibase(converter(mask, data), 2, 0);
	len = ft_strlen(num);
	nzeros = (mask->accurancy > len) ? mask->accurancy - len : 0;
	nspaces = (mask->width > len + nzeros) ? mask->width - nzeros - len : 0;
	(mask->sharp == 1) ? nspaces -= 2 : 0;
	if (!mask->minus && (!mask->null || nzeros > 0 || mask->accurancy == -1))
		n += ft_space_null_di(nspaces, mask);
	(mask->sharp == 1) ? n += write(1, "0b", 2) : 0;
	n += print_zero(nzeros);
	n += write(1, num, len);
	(mask->minus) ? n += ft_space_null_di(nspaces, mask) : 0;
	free(num);
	return (n + 1);
}

static int		hex(int nb, int recursion)
{
	char	c;

	(recursion == 1) ? hex(nb / 16, recursion - 1) : 0;
	if (nb % 16 < 10)
		c = (nb % 16) + '0';
	else
		c = 'a' + ((nb % 16) - 10);
	write(1, &c, 1);
	return (2);
}

static int		content(unsigned char *bytes, int counter, int width)
{
	int		i;
	int		j;
	int		n;

	n = 0;
	j = counter - 1;
	while (++j < width)
		n += (j % 2) ? write(1, "   ", 3) : write(1, "  ", 2);
	i = -1;
	while (++i < counter)
	{
		(bytes[i] > 31 && bytes[i] < 127) ? n += write(1, &bytes[i], 1) : 0;
		(bytes[i] < 32 || bytes[i] > 126) ? n += write(1, ".", 1) : 0;
	}
	n += write(1, "\n", 1);
	return (n);
}

int				print_memory(t_mask *mask, void *data)
{
	int				i;
	int				counter;
	unsigned char	bytes[16];
	int				n;
	int				width;

	i = -1;
	n = 0;
	counter = 0;
	if (!data)
		return (0);
	width = (mask->width > 0) ? mask->width : 16;
	(width % 2) ? width++ : 0;
	while (++i < mask->accurancy)
	{
		bytes[counter++] = *(int *)(data + i);
		n += hex((int)bytes[counter - 1], 1);
		(i % 2 == 1) ? n += write(1, " ", 1) : 0;
		(counter == width) ? n += content(bytes, counter, width) : 0;
		(counter == width) ? counter = 0 : 0;
	}
	if (mask->accurancy > 0)
		(counter != 0) ? n += content(bytes, counter, width) : 0;
	return (n);
}
