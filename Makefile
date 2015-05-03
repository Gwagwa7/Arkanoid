# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apantiez <apantiez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 15:21:48 by apantiez          #+#    #+#              #
#    Updated: 2015/05/03 22:32:58 by mcassagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		arkanoid

SRC =		srcs/

INCDIR =	includes/

SOURCE =	$(SRC)draw_score.c		\
			$(SRC)check.c			\
			$(SRC)draw_ball.c		\
			$(SRC)draw_blocks.c		\
			$(SRC)draw_board.c		\
			$(SRC)draw_score.c		\
			$(SRC)free_clear.c		\
			$(SRC)get_maxi.c		\
			$(SRC)hit.c				\
			$(SRC)init.c			\
			$(SRC)init_block.c		\
			$(SRC)init_levels.c		\
			$(SRC)main.c			\
			$(SRC)move.c			\
			$(SRC)parse_file.c		\
			$(SRC)parsing.c			\
			$(SRC)rest_block.c		\
			$(SRC)tools.c

OBJ =		$(SOURCE:.c=.o)

LIB_GLFW =	glfw/src/libglfw3.a

LIB =		libft/libft.a

LIB_DIR =	libft

CC =		gcc

LINK_FLAG =	-L libft -lft -L glfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

FLAG =		-I $(INCDIR) -I glfw/include/ -g -Wall -Wextra -Werror -I $(LIB_DIR)/inc

RED = \033[33;31m
BLUE = \033[33;34m
GREEN = \033[33;32m
RESET = \033[0m

.PHONY: all re fclean

all: $(NAME)

$(LIB): 
	@make -C $(LIB_DIR)

$(LIB_GLFW):
	git submodule init
	cd glfw && cmake .
	make -C glfw

$(NAME): $(LIB) $(LIB_GLFW) $(OBJ)
	@$(CC) -o $(NAME) $(FLAG) $^ $(LIB_COMP) $(LINK_FLAG)
	@rm -f $(DEP).gch
	@echo "[$(GREEN)Compilation $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

%.o: %.c
	@$(CC) -c -o $@ $(FLAG) $^ 

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJ)
	@echo "[$(RED)Supression des .o de $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@make -C glfw clean
	@rm -f $(NAME)
	@echo "[$(RED)Supression de $(BLUE)$(NAME) $(GREEN)ok$(RESET)]"

re: fclean all
