/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 13:40:09 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:44:25 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <arkanoid.h>
#include <libft.h>

static void	draw_stuff(t_game *game)
{
	draw_board(game);
	draw_blocks(game);
	draw_ball(game);
	draw_score(game->score, 1.8f, -1.6f);
	draw_score(game->life, 0.2f, -1.6f);
}

static void	load_level(t_game *game, t_level *level)
{
	game->level_height = level->height;
	game->level_width = level->width;
	game->blocks = level->blocks;
	game->offset_x = WIN_WIDTH / level->width - 1;
	game->offset_y = (WIN_HEIGHT - 200) / level->height - 1;
	game->started = 1;
	game->win = 0;
	init_ball(game);
}

static void	do_gl_stuff(t_game *game)
{
	int			width;
	int			height;

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glfwGetFramebufferSize(game->window, &width, &height);
}

static void	app(t_game *game)
{
	t_level		*current;

	init_glfw(game);
	current = game->levels;
	while (current)
	{
		load_level(game, current);
		while (!glfwWindowShouldClose(game->window) && !game->win)
		{
			update_time(game);
			if (game->started && !game->paused)
			{
				do_gl_stuff(game);
				move_ball(game);
				check_collision(game);
				draw_stuff(game);
				check_game_state(game);
				glfwSwapBuffers(game->window);
				usleep(12500);
			}
			glfwPollEvents();
			usleep(100);
		}
		current = current->next;
	}
}

int			main(int ac, char **av)
{
	t_game	*game;

	(void)ac;
	game = uf_get_game();
	create_game(game, av[1]);
	app(game);
	terminate_glfw(game);
	return (0);
}
