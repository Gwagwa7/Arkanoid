/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_maxi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 22:04:03 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:04:14 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

void		get_block_maxi(t_block *block, float point[4][2], t_game *game)
{
	float	width;
	float	height;
	float	tmp_x;
	float	tmp_y;

	tmp_x = (float)block->pos.x * game->offset_x;
	tmp_y = ((float)block->pos.y) * game->offset_y;
	tmp_x = (tmp_x - ((float)WIN_WIDTH / 2.0f));
	tmp_x = tmp_x / (WIN_WIDTH / 2);
	tmp_y = (tmp_y - (((float)WIN_HEIGHT) / 2.0f));
	tmp_y = -tmp_y / (WIN_HEIGHT / 2);
	width = 2.0f / (float)game->level_width;
	height = 2.0f / (float)game->level_height;
	point[0][0] = tmp_x;
	point[0][1] = tmp_y;
	point[1][0] = tmp_x + width;
	point[1][1] = tmp_y;
	point[2][0] = tmp_x;
	point[2][1] = tmp_y - height;
	point[3][0] = tmp_x + width;
	point[3][1] = tmp_y - height;
}

void		get_ball_maxi(t_ball *ball, float point[4][2])
{
	float	tmp_x;
	float	tmp_y;
	float	t;
	float	theta;

	tmp_x = ((float)ball->pos.x - ((float)WIN_WIDTH / 2)) / (float)WIN_WIDTH;
	tmp_y = (((float)ball->pos.y - 200) - ((float)WIN_HEIGHT / 2))
		/ (float)WIN_HEIGHT;
	theta = 2.0f * 3.1415926f * 10.0f / 10.0f;
	t = (float)ball->rayon / ((float)WIN_WIDTH / 4) * get_cos_sin(0, 0);
	point[0][0] = tmp_x;
	point[0][1] = tmp_y + t;
	theta = 2.0f * 3.1415926f * 2.5f / 10.0f;
	t = (float)ball->rayon / ((float)WIN_HEIGHT / 4) * get_cos_sin(3, 1);
	point[1][0] = tmp_x + t;
	point[1][1] = tmp_y;
	theta = 2.0f * 3.1415926f * 5.0f / 10.0f;
	t = (float)ball->rayon / ((float)WIN_HEIGHT / 4) * get_cos_sin(5, 0);
	point[2][0] = tmp_x;
	point[2][1] = tmp_y - t;
	theta = 2.0f * 3.1415926f * 7.50f / 10.0f;
	t = (float)ball->rayon / ((float)WIN_HEIGHT / 4) * get_cos_sin(8, 1);
	point[3][0] = tmp_x - t;
	point[3][1] = tmp_y;
}
