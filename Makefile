CC = gcc
CFLAGS = -Wall -Wextra -Werror -I -g
NAME = ft_ls

_DEPS_MD5 = ft_ls.h
DEPS = $(LS_DIR)/$(_DEPS_LS)

SRC = ft_getopt.c \

LS_DIR = ./ft_ls
LS_SRC =main.c \
		ft_getopt \
		ft_ls.c \
		
LS = $(patsubst %, $(LS_DIR)/%, $(LS_SRC))

SRC_OBJ =$(SRC:.c=.o)
LS_OBJ = $(LS:.c=.o)

OBJ = $(SRC_OBJ) $(LS_OBJ)
LIBS = ./ft_printf/libftprintf.a

all: $(NAME)

$(LIBS):
	@+$(MAKE) -C ./libft


%.o: %.c $(DEPS)
	@echo "\033[0;32m\c"
	$(CC) -g -c -o $@ $< $(CFLAGS)
	@echo "\033[0m\c"

$(NAME): $(OBJ) $(LIBS)
	@echo "\033[0;35m\c"
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "\033[0m\c"

ls: $(LS_OBJ) $(LIBS)
	@echo "\033[0;34m\c"
	$(CC) -g -o ft_ssl_$@ $^ $(CFLAGS) $(LIBS)
	@echo "\033[0m\c"

clean:
	@/bin/rm -f $(OBJ)
	@+$(MAKE) clean -C ./libft

fclean: clean
	@/bin/rm -f $(NAME)
	@+$(MAKE) fclean -C ./libft


re: fclean all

.PHONY: clean fclean re