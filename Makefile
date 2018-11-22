.PHONY: all clean fclean re

NAME = libftprintf.a

SRC = ft_printf.c csp.c decimal_int.c ft_isdigit.c ft_itoa.c itoa_base.c \
		ft_strlen.c mask.c unsigned.c ft_atoi.c float.c for_all.c

SRO = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Wextra -Werror $(SRC)
	@ar rc $(NAME) $(SRO)
	@ranlib $(NAME)

clean:
	/bin/rm -rf $(SRO)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
