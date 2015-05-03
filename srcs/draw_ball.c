/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ball.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:35:16 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:25:47 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

float	get_cos_sin(int i, int cos)
{
	static float	tab[10][2] = {

	{ 1.000000, 0.000000 }, { 0.766044, 0.642788 }, { 0.173648, 0.984808 },
	{ -0.500000, 0.866025 }, { -0.939693, 0.342020 },
	{ -0.939693, -0.342020 }, { -0.500000, -0.866025 },
	{ 0.173648, -0.984808 }, { 0.766044, -0.642788 },
	{ 1.000000, -0.000000 }
	};
	if (cos)
		return (tab[i][0]);
	else
		return (tab[i][1]);
}

void	draw_ball(t_game *game)
{
	int				i;
	float			xy[2];
	float			c[2];

	c[0] = ((float)game->ball.pos.x - ((float)WIN_WIDTH / 2))
		/ (float)WIN_WIDTH;
	c[1] = ((float)game->ball.pos.y - ((float)WIN_HEIGHT / 2))
		/ (float)WIN_HEIGHT;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	i = 0;
	while (i <= 9)
	{
		xy[0] = (float)game->ball.rayon / ((float)WIN_WIDTH / 4)
			* get_cos_sin(i, 1);
		xy[1] = (float)game->ball.rayon / ((float)WIN_WIDTH / 4)
			* get_cos_sin(i, 0);
		glVertex2f(xy[0] + c[0], xy[1] + c[1]);
		i++;
	}
	glEnd();
}
