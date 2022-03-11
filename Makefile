# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gogrkovi <gogrkovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/19 15:22:51 by gogrkovi          #+#    #+#              #
#    Updated: 2019/10/10 16:10:38 by gogrkovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	ft_ls

SRC =   affiche.c		\
		main.c			\
		core.c			\
		element.c	 	\
		error.c			\
		recursion.c		\
		size.c			\
		sort.c			\
		time.c			\
		print.c			\

OBJ =   $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

all:$(NAME)

$(NAME): $(OBJ)
		@make -C libft/
		@$(CC) $(CFLAGS) ./libft/libft.a $(SRC) -o $(NAME)

fclean: clean
		@rm -f $(NAME)
		@make -C libft/ fclean

clean:
		@rm -f $(OBJ)
		@make -C libft/ clean

re:     fclean all

.PHONY: all fclean clean re
