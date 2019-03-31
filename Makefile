# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/20 14:19:43 by dezzeddi          #+#    #+#              #
#    Updated: 2019/03/08 18:43:00 by dezzeddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c parse_flags.c print_functions.c ft_lstfuncs.c sort_functions.c ft_mergesort.c ft_recursive.c utils.c

FLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRC:.c=.o)

LIBFT = libft

all: $(NAME)

$(NAME):
	make -C $(LIBFT) 
	gcc $(FLAGS) -c $(SRC) -I./
	gcc $(FLAGS) $(OBJS) -L./libft -lft -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

re: fclean all
