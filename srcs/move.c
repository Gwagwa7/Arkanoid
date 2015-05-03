/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:50:59 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 21:52:15 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

void		move_board(t_game *game, int sens)
{
	int	i;

	i = 0;
	if (sens)
	{
		while (i < game->board.speed && game->board.pos.x > 50)
		{
			--game->board.pos.x;
			++i;
		}
	}
	else if (game->board.pos.x < 1200)
	{
		while (i < game->board.speed && game->board.pos.x < 750)
		{
			++game->board.pos.x;
			++i;
		}
	}
}

void		move_ball(t_game *game)
{
	game->ball.pos.x += game->ball.direction.x;
	if (game->ball.pos.x >= 1200 || game->ball.pos.x <= -400)
		game->ball.direction.x = -game->ball.direction.x;
	game->ball.pos.y += game->ball.direction.y;
	if (game->ball.pos.y >= 1200)
		game->ball.direction.y = -game->ball.direction.y;
}
