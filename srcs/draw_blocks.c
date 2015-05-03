/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:36:14 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 21:37:09 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

static void	set_color(t_block_type type)
{
	if (type == BLOCK_EASY)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if (type == BLOCK_MEDIUM)
		glColor3f(0.0f, 0.0f, 1.0f);
	else if (type == BLOCK_HARD)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if (type == BLOCK_IMMORTAL)
		glColor3f(0.5f, 0.5f, 0.5f);
	else if (type == BLOCK_EMPTY)
		glColor3f(0.1f, 0.1f, 0.1f);
	else if (type == BLOCK_BONUS)
		glColor3f(0.7f, 0.7f, 0.7f);
}

void		draw_block(t_game *game, t_block *block)
{
	float	x;
	float	y;
	float	width;
	float	height;

	x = (float)block->pos.x * game->offset_x;
	y = ((float)block->pos.y) * game->offset_y;
	x = (x - ((float)WIN_WIDTH / 2.0f));
	x = x / (WIN_WIDTH / 2);
	y = (y - ((float)WIN_HEIGHT / 2.0f));
	y = -y / (WIN_HEIGHT / 2);
	glBegin(GL_QUADS);
	set_color(block->type);
	width = (float)game->offset_x / (float)WIN_WIDTH * 2.0f;
	height = (float)game->offset_y / (float)WIN_HEIGHT * 2.0f;
	glVertex2f(x, y);
	glVertex2f(x, y - height);
	glVertex2f(x + width, y - height);
	glVertex2f(x + width, y);
	glEnd();
}

void		draw_blocks(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->level_height)
	{
		x = 0;
		while (x < game->level_width)
		{
			draw_block(game, &(game->blocks[y][x]));
			++x;
		}
		++y;
	}
}
