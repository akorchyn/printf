/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:46:19 by akorchyn          #+#    #+#             */
/*   Updated: 2018/11/13 11:46:20 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include <string.h>

# define CHAR 0
# define STRING 1
# define POINTER 2
# define DECIMAL 3
# define INT 4
# define U_OCTAL 5
# define U_DECIMAL 6
# define U_HEX_LOWER 7
# define U_HEX_UPPER 8
# define FLOAT 9
# define PERCENT 10
# define UNICODE_CH 11
# define UNICODE_STR 12
# define BAD_TYPE 13

# define CHECK(x) if (x != -1) return (ft_space_null_di(mask->width, mask) + x);
# define NILL(x) if (x != 0) return (x);

int					ft_printf(const char *format, ...);

/*
**	l_big --> L
*/

typedef struct		s_vars
{
	unsigned char	type : 4;
	unsigned char	h : 1;
	unsigned char	hh : 1;
	unsigned char	l : 1;
	unsigned char	z : 1;
	unsigned char	j : 1;
	unsigned char	ll : 1;
	unsigned char	l_big : 1;
	unsigned char	null : 1;
	unsigned char	space : 1;
	unsigned char	plus : 1;
	unsigned char	minus : 1;
	unsigned char	sharp : 1;
	int				width;
	int				accurancy;
}					t_mask;

/*
** Функции вывода.
*/

int					ft_putch(t_mask *mask, void	*s);
int					ft_putstring(t_mask *mask, void *s);
int					bad_type(t_mask *mask, void *s);
int					pointer(t_mask *mask, void *data);
int					decimal(t_mask *mask, void *data);
int					octal(t_mask *mask, void *data);
int					hexdecimal_up(t_mask *mask, void *data);
int					hexdecimal_low(t_mask *mask, void *data);
int					unsigned_decimal(t_mask *mask, void *data);
int					percent(t_mask *mask, void *data);
int					print_float(t_mask *mask, long double data, int count);
int 				print_unicode(wchar_t c);

/*
**	Вспомогательные функции для функций вывода.
**	ft_space_null выводит нули, либо пробелы в
**  в зависимости от флага 0 и ширины.
**  null_di учитывает еще точность поэтому иногда
**  флаг ноль игнорируется.
**  Print zero выводит n нулей
**  u_null проверяет на ноль и точность 0.
*/

int					ft_space_null(int n, t_mask *mask);
int					ft_space_null_di(int n, t_mask *mask);
int					u_null(t_mask *mask, void *data);
int					print_zero(int n);

/*
**	Читает маску %.
*/

int					read_mask(char *str, t_mask **mask);

/*
** Измененные (или нет) библиотечные функции.
** strlen не изменен, isdigit также.
** ibase = Itoa_base работает только с
** положительными цифрами.
** itoa приведен к типу __int 128.
*/

int					ft_strlen(const char *str);
int					ft_isdigit(int c);
char				*ibase(__uint128_t nb, int base, int let_case);
int					ft_atoi(const char *str);
char				*ft_itoa(__int128 n);
char 				*ft_strrev(char *str);

#endif
