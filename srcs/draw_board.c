/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 21:48:55 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 21:49:26 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

void		draw_board(t_game *game)
{
	float	x;
	float	y;

	x = (float)game->board.pos.x;
	x = (x - ((float)WIN_WIDTH / 2.0f));
	x = x / (WIN_WIDTH / 2);
	y = (float)game->board.pos.y;
	y = (y + ((float)WIN_HEIGHT / 2.0f));
	y = y / (WIN_HEIGHT / 2);
	glBegin(GL_LINES);
	glColor3f(0.9f, 0.5f, 0.3f);
	glVertex2f(x - (game->board.width / 2), y);
	glVertex2f(x + (game->board.width / 2), y);
	glEnd();
}
