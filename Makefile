all:
	git submodule init
	git submodule update
	gcc -o arkanoid -I ./includes -I./glfw/include -L ./libft -lft -L ./ -lglfw3 srcs/*.c
