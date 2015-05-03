/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:33:37 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:26:25 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <arkanoid.h>
#include <libft.h>

t_game	*uf_get_game(void)
{
	static t_game	*game;

	if (game == NULL)
	{
		game = malloc(sizeof(*game));
		if (game == NULL)
			return (NULL);
	}
	return (game);
}

void	terminate_glfw(t_game *game)
{
	glfwDestroyWindow(game->window);
	glfwTerminate();
	exit(1);
}

void	update_time(t_game *game)
{
	game->last_time = game->time;
	game->time = glfwGetTime();
	game->dt = game->time - game->last_time;
}

void	create_game(t_game *game, char *player_name)
{
	game->life = 2;
	game->score = 0;
	game->paused = 0;
	game->win = 0;
	game->time = 1;
	game->last_time = 1;
	game->difficulty = EASY;
	game->levels = NULL;
	game->level_height = 5;
	game->level_width = 20;
	game->blocks = NULL;
	init_ball(game);
	init_board(game);
	game->started = 0;
	if (player_name)
		game->player_name = player_name;
	else
		game->player_name = ft_strdup("Player One\n");
	game->window = NULL;
	game->time = glfwGetTime();
	game->last_time = glfwGetTime();
	game->dt = 1.0f;
	parse_file(game);
	if (game->levels == NULL)
		exit(0);
}
