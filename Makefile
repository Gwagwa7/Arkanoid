# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apantiez <apantiez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 15:21:48 by apantiez          #+#    #+#              #
#    Updated: 2015/05/02 20:03:03 by apantiez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBFT = -L ./libft -lft -I ./libft

SRC =

OBJ = $(SRC:.c=.o)

NAME = Arkanoid

all: $(NAME)

$(NAME): $(OBJ)
	git submodule init
	git submodule update
	mkdir ./glfw/glfw-build
	cd glfw/glfw-build/ && cmake ../
	make -C ./libft
#	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFT)

%.o : %.c
	$(CC) -c $(CFLAGS) -I ./libft $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re : fclean all
