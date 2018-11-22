cmake_minimum_required(VERSION 3.12)
project(printf C)

set(CMAKE_C_STANDARD 99)

add_executable(printf ft_printf.c csp.c decimal_int.c ft_isdigit.c ft_itoa.c itoa_base.c ft_strlen.c mask.c unsigned.c ft_atoi.c float.c for_all.c)