/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:58:37 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:46:48 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

void		ball_hit_block(t_block *block, t_ball *ball, t_game *game, int sens)
{
	static double	last_change = 0;

	if (block->type != BLOCK_EMPTY)
	{
		if (block->type != BLOCK_IMMORTAL)
			game->score += 10;
		if (glfwGetTime() - last_change >= 0.2)
		{
			if (sens == 1)
				ball->direction.y = -ball->direction.y;
			else if (sens == 2)
				ball->direction.x = -ball->direction.x;
			else if (sens == 3)
				ball->direction.y = -ball->direction.y;
			else if (sens == 4)
				ball->direction.x = -ball->direction.x;
			last_change = glfwGetTime();
		}
	}
	--block->life;
	if (block->life <= 0 && block->type != BLOCK_IMMORTAL)
		block->type = BLOCK_EMPTY;
}

int			ball_hit_board(t_game *game)
{
	float			south[2];
	float			board[2];
	float			tmp[2];

	south[0] = ((float)game->ball.pos.x - ((float)WIN_WIDTH / 2))
		/ (float)WIN_WIDTH;
	south[1] = ((float)game->ball.pos.y - ((float)WIN_HEIGHT / 2))
		/ (float)WIN_HEIGHT;
	tmp[0] = 2.0f * 3.1415926f * 0.5f;
	tmp[1] = (float)game->ball.rayon / ((float)WIN_HEIGHT / 4) * 0.0548036f;
	south[1] -= tmp[1];
	board[0] = ((float)game->board.pos.x - ((float)WIN_WIDTH))
		/ (float)WIN_WIDTH;
	board[1] = ((float)game->board.pos.y) / (float)WIN_HEIGHT + 0.1f;
	board[0] = board[0] * 2.0f;
	board[0] += 1.0f;
	if (south[0] >= board[0] - (game->board.width / 2) && south[0] <= board[0]
			+ (game->board.width / 2) && south[1] <= board[1])
		return (1);
	return (0);
}
