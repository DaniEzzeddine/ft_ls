# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/20 14:19:43 by dezzeddi          #+#    #+#              #
#    Updated: 2019/02/28 18:24:56 by dezzeddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c  ulits.c list_function.c print_functions.c sort_functions.c ft_ls.c ft_mergesort.c

FLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRC:.c=.o)

LIBFT = libft

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc $(FLAGS) -c $(SRC)
	gcc $(FLAGS) $(OBJS) -L./libft -lft -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

re: fclean all
