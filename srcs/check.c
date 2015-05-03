/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:59:14 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:46:06 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arkanoid.h>

int			touch(float block[4][2], float x, float y)
{
	if (x >= block[0][0] && x <= block[1][0])
	{
		if (y >= block[3][1] && y <= block[4][1])
			return (1);
	}
	return (0);
}

int			check_block_collision(t_block *block, t_ball *ball, t_game *game)
{
	float	p_ball[4][2];
	float	p_block[4][2];

	get_ball_maxi(ball, p_ball);
	get_block_maxi(block, p_block, game);
	if (touch(p_block, p_ball[0][0], p_ball[0][1]))
		return (1);
	if (touch(p_block, p_ball[1][0], p_ball[1][1]))
		return (2);
	if (touch(p_block, p_ball[2][0], p_ball[2][1]))
		return (3);
	if (touch(p_block, p_ball[3][0], p_ball[3][1]))
		return (4);
	return (0);
}

void		check_blocks_collision(t_game *game)
{
	t_block	*block;
	t_ball	*ball;
	int		i;
	int		j;
	int		ret;

	ball = &game->ball;
	i = 0;
	while (i < game->level_height)
	{
		j = 0;
		while (j < game->level_width)
		{
			block = &(game->blocks[i][j]);
			if (block->type != BLOCK_EMPTY)
			{
				if ((ret = check_block_collision(block, ball, game)))
				{
					ball_hit_block(block, ball, game, ret);
				}
			}
			++j;
		}
		++i;
	}
}

void		check_collision(t_game *game)
{
	t_ball			*ball;
	static double	last_change = 0;

	ball = &(game->ball);
	if (ball_hit_board(game) && glfwGetTime() - last_change >= 0.2f)
	{
		game->ball.direction.y *= -1;
		last_change = glfwGetTime();
	}
	check_blocks_collision(game);
	if (ball->pos.y <= -400)
	{
		--game->life;
		init_ball(game);
	}
}

void		check_game_state(t_game *game)
{
	if (!rest_destuctible_block(game))
		game->win = 1;
	if (game->life <= 0)
		game->win = -1;
}
