# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maljean <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 03:01:42 by maljean           #+#    #+#              #
#    Updated: 2018/08/19 20:19:48 by dezzeddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

FLAGS = -Wall -Wextra -Werror -O2

LIB = libft.a

SOURCES = convert.c \
		  ft_handle_addr.c \
		  ft_handle_char.c \
		  ft_wstr_help.c \
		  ft_handle_int.c \
		  ft_handle_str.c \
		  ft_handle_wstr.c \
		  ft_printf.c \
		  convert_spec.c \
		  ft_handle_binary.c \
		  ft_handle_hex.c \
		  ft_handle_octal.c \
		  ft_handle_uint.c \
		  ft_parse_specifier.c

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) -c $(SOURCES) -I ..

clean:
	rm -f $(OBJS)

re: fclean all
