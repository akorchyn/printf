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
# define BAD_TYPE 11

# define CHECK(x) if (x != -1) return (ft_space_null_di(mask->width, mask) + x);
# define NILL(x) if (x == -1) return (ft_space_null_di(mask->width, mask) + 6);

typedef struct		s_vars
{
	unsigned char	type : 4;
	unsigned char	h : 1;
	unsigned char	hh : 1;
	unsigned char	l : 1;
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

typedef	int			(*t_functions)(t_mask *, void *);
int					ft_putch(t_mask *mask, void	*s);
int					ft_putstring(t_mask *mask, void *s);
int					bad_type(t_mask *mask, void *s);
int					pointer(t_mask *mask, void *data);
int					decimal(t_mask *mask, void *data);
int					octal(t_mask *mask, void *data);
int					hexdecimal_up(t_mask *mask, void *data);
int					hexdecimal_low(t_mask *mask, void *data);
int					unsigned_decimal(t_mask *mask, void *data);


int					ft_space_null(int n, t_mask *mask);
int					ft_space_null_di(int n, t_mask *mask);
int					read_mask(char *str, t_mask **mask);

int					ft_strlen(const char *str);
char				*ft_itoa_base(unsigned long long int nb,
	int base, int let_case);
int					ft_atoi(char *str);
int					ft_isdigit(int c);
char				*ft_itoa(long long n);

#endif
