# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snettah <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/26 12:01:48 by snettah           #+#    #+#              #
#    Updated: 2016/05/02 16:20:49 by ybarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nmap

CC = clang

#CFLAGS = -Wall -Werror -Wextra

SRC_PATH = ./srcs/

SRC_NAME =	main.c \
			parser.c \
			services.c \
			init_options.c \
			helper.c \
			ports.c \
			scan.c \
			init_global.c \
			connect.c \
			loop.c

OBJ_PATH = ./obj/

OBJ_NAME = $(SRC_NAME:.c=.o)


OBJ_PATH = ./obj/

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_PATH = ./inc/

INC_PATH_LIBFT = ./libft/includes

LIB_PATH = ./libft/

LIB_NAME = libft.a

#MINI_LIB = -L/usr/X11/lib -lmlx -lXext -lX11

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))

COMPILE = echo "\033[36mCompile ....\033[0m"
COMPILED = echo "\033[32mCompiled Successfully\033[0m"
CLEAN = echo "\033[38mClean ....\033[0m"
CLEANED = echo "\033[32mCleaned Successfully\033[0m"

all: libmake $(NAME)

$(NAME): $(OBJ) $(LIB)
	@$(COMPILE)
	@$(CC) $(CFLAGS) -o $(NAME) -I$(INC_PATH) -I$(INC_PATH_LIBFT) \
		$(LIB) $(OBJ) $(LIB)
	@$(COMPILED)

libmake:
	@(make -C libft/)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo '' > /dev/null
	@$(CC) $(CFLAGS) -o $@ -I$(INC_PATH) -I$(INC_PATH_LIBFT) -c $<

clean: libclean
	@$(CLEAN)
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo '' > /dev/null
	@$(CLEANED)

libclean:
	@(make -C libft/ clean)

fclean: clean libfclean
	@rm -f $(NAME)

libfclean:
	@(make -C libft/ fclean)

re: fclean all
