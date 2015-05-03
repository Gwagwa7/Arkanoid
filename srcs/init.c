/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:53:49 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:36:13 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <arkanoid.h>

static void	key_callback(GLFWwindow *window,\
		int key, int scancode, int action, int mods)
{
	t_game *game;

	(void)mods;
	(void)scancode;
	game = uf_get_game();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_LEFT)
		move_board(game, 1);
	else if (key == GLFW_KEY_RIGHT)
		move_board(game, 0);
	else if (key == GLFW_KEY_P)
		game->paused = 1;
	else if (key == GLFW_KEY_O)
		game->paused = 0;
}

void		init_ball(t_game *game)
{
	game->ball.speed = 500;
	game->ball.pos.x = 400;
	game->ball.pos.y = -250;
	game->ball.direction.x = 10;
	game->ball.direction.y = 5;
	game->ball.rayon = WIN_WIDTH / 200;
}

void		init_board(t_game *game)
{
	game->board.pos.x = 400;
	game->board.pos.y = -750;
	game->board.speed = 75;
	game->board.width = 0.3f;
}

void		init_glfw(t_game *game)
{
	if (!glfwInit())
		exit(0);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	game->window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT,
			"Arkanoid", NULL, NULL);
	if (!game->window)
	{
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(game->window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(game->window, key_callback);
}
