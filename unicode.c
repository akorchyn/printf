/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 12:44:50 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/24 13:08:38 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define TWO_BIT 0b11000000
#define THREE_BIT 0b11100000
#define FOUR_BIT 0b11110000
#define OTHER_BIT 0b10000000

#define MASK 0b111111

int				active_bits(wchar_t c)
{
	int		i;

	i = 0;
	while (c > 0)
	{
		i++;
		c /= 2;
	}
	return (i);
}

static int		first_num(wchar_t c, int bits)
{
	int		bit;
	int		shift;

	bit = 0;
	(bits > 7) ? bit = TWO_BIT : 0;
	(bits > 11) ? bit = THREE_BIT : 0;
	(bits > 16) ? bit = FOUR_BIT : 0;
	shift = bits - (bits % 6);
	return (c >> shift | bit);
}

int				print_unicode(wchar_t c)
{
	int				bits;
	unsigned char	ch[4];
	int				i;

	bits = active_bits(c);
	i = 0;
	ch[0] = (char)c;
	(bits > 7) ? ch[i++] = first_num(c, bits) : 0;
	(bits > 16) ? ch[i++] = OTHER_BIT | (MASK & (c >> 12)) : 0;
	(bits > 11) ? ch[i++] = OTHER_BIT | (MASK & (c >> 6)) : 0;
	(bits > 7) ? ch[i++] = OTHER_BIT | (MASK & c) : 0;
	(i == 0) ? i = 1 : 0;
	write(1, ch, i);
	return (i);
}
