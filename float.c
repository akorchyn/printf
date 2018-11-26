/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:21:39 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/21 13:21:40 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Функция floating_value немного странная и по большей мере похожа на костыль.
** Она записывает остачу в k но после первой цифры(изначально 1). Первая цифра
** служит, для того что бы не потерять нули и проверить инкрементнится ли
** целая часть. Если первая цифра равна двум значит должна увеличится целая
** часть.
** Больше равно т.к. мы хотим увидить на одну цифру больше чем говорит нам
** точность.
*/

__int128		floating_value(int accurancy, long double data)
{
	__uint128_t		c;
	__uint128_t		k;

	k = 1;
	c = data;
	while (accurancy-- >= 0)
	{
		data = (data - c) * 10;
		c = data;
		k = k * 10 + c % 10;
	}
	if (k % 10 > 4)
		k += 10;
	return (k);
}

int				plus_minus(t_mask *mask, int minus)
{
	if (mask->plus && minus == 0)
		return (write(1, "+", 1));
	else if (minus == 1)
		return (write(1, "-", 1));
	return (0);
}

int				ft_abs(long double *data)
{
	int minus;

	minus = 0;
	if (*data < 0)
	{
		minus = 1;
		*data *= -1;
	}
	return (minus);
}

int				print_float(t_mask *mask, long double data, int count)
{
	char		*int_data;
	char		*fldata;
	int			acc;
	int			minus;
	int			nspaces;

	acc = (mask->accurancy != -1) ? mask->accurancy : 6;
	minus = ft_abs(&data);
	fldata = ibase(floating_value(acc, data), 10, 1);
	int_data = (*fldata == '2') ? ibase(data + 1, 10, 1) : ibase(data, 10, 1);
	nspaces = (mask->width > acc + ft_strlen(int_data))
			? mask->width - acc - ft_strlen(int_data) : 0;
	(mask->space == 1 && data > 0 && !nspaces) ? nspaces++ : 0;
	(mask->plus || minus) ? nspaces-- : 0;
	(acc > 0 || mask->sharp) ? nspaces-- : 0;
	(!mask->minus && !mask->null) ? count += ft_space_null(nspaces, mask) : 0;
	count += plus_minus(mask, minus);
	(!mask->minus && mask->null) ? count += ft_space_null(nspaces, mask) : 0;
	count += write(1, int_data, ft_strlen(int_data));
	(mask->accurancy != 0 || mask->sharp) ? count += write(1, ".", 1) : 0;
	(mask->accurancy != 0) ? count += write(1, fldata + 1, acc) : 0;
	(mask->minus) ? count += ft_space_null(nspaces, mask) : 0;
	free(fldata);
	free(int_data);
	return (count);
}
