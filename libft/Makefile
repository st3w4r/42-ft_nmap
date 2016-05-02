# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snettah <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/06 18:52:02 by snettah           #+#    #+#              #
#    Updated: 2016/05/02 18:18:53 by ybarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_tolower.c \
		  ft_toupper.c ft_isalpha.c ft_isalnum.c ft_strcat.c ft_strncat.c\
		  ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
		  ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isdigit.c ft_isascii.c \
		  ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
		  ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
		  ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		  ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		  ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putnbr_fd.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strjoin.c \
		  ft_strtrim.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
		  ft_itoa.c ft_lstiter.c ft_lstmap.c ft_strsplit.c ft_print_list.c \
		  ft_push_back.c ft_list_last.c btree_create_node.c \
		  btree_apply_prefix.c btree_apply_infix.c btree_insert_data.c \
		  ft_nbrendl.c ft_tablen.c ft_isblank.c ft_ltrim.c \
		  ft_epur_str.c ft_add_to_tab.c ft_arrlen.c ft_arrfree.c \
		  ft_is_number.c ft_get_next_line.c ft_error.c

SRCS = $(addprefix srcs/, $(SOURCES))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo  "\r\033[0;34;22m✅  Make 💟 \033[0m\033[K"
	@printf "\033[32m✅ \033[0m \033[33m\033[4mlibft.a\033[0m \n"
	@ranlib $(NAME)
	

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $^ -Iincludes/

clean:
	@echo -en "\r\033[0;31;124m❌  CLEAN *.o \033[0m\033[K"
	@rm -f $(OBJS)

fclean: clean
	@echo -en "\r\033[0;31;124m❌  FCLEAN $(NAME) \033[0m\033[K"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
