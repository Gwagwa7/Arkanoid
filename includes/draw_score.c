/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_score.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apantiez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 15:26:40 by apantiez          #+#    #+#             */
/*   Updated: 2015/05/03 15:27:49 by apantiez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <arkanoid.h>

static int  **init_tab(int tab[10][7])
{
	int		i;
	int		y;
	static int	**ret_tab;


	if (ret_tab == NULL)
	{
		ret_tab = (int **)malloc(sizeof(int *) * 10);
		i = 0;
		while (i < 10)
		{
			ret_tab[i] = (int *)malloc(sizeof(int) * 7);
			y = 0;
			while (y < 7)
			{
				ret_tab[i][y] = tab[i][y];
				y++;
			}
			i++;
		}
	}
	return (ret_tab);
}




static int		**tab_number()
{
	int i;
	int y;
	int	tab[10][7] = {
		{DIGIT_TOP, DIGIT_TOP_LEFT, DIGIT_TOP_RIGHT, DIGIT_EMPTY, DIGIT_BOT_LEFT, DIGIT_BOT_RIGHT, DIGIT_BOT},
		{DIGIT_EMPTY, DIGIT_EMPTY, DIGIT_TOP_RIGHT, DIGIT_EMPTY, DIGIT_EMPTY, DIGIT_BOT_RIGHT, DIGIT_EMPTY},
		{DIGIT_TOP, DIGIT_EMPTY, DIGIT_TOP_RIGHT, DIGIT_MID, DIGIT_BOT_LEFT, DIGIT_EMPTY, DIGIT_BOT},
		{DIGIT_TOP, DIGIT_EMPTY, DIGIT_TOP_RIGHT, DIGIT_MID, DIGIT_EMPTY, DIGIT_BOT_RIGHT, DIGIT_BOT},
		{DIGIT_EMPTY, DIGIT_TOP_LEFT, DIGIT_TOP_RIGHT, DIGIT_MID, DIGIT_EMPTY, DIGIT_BOT_RIGHT, DIGIT_EMPTY},
		{DIGIT_TOP, DIGIT_TOP_LEFT, DIGIT_EMPTY, DIGIT_MID, DIGIT_EMPTY, DIGIT_BOT_RIGHT, DIGIT_BOT},
		{DIGIT_TOP, DIGIT_TOP_LEFT, DIGIT_EMPTY, DIGIT_MID, DIGIT_BOT_LEFT, DIGIT_BOT_RIGHT, DIGIT_BOT},
		{DIGIT_TOP, DIGIT_EMPTY, DIGIT_TOP_RIGHT, DIGIT_EMPTY, DIGIT_EMPTY, DIGIT_BOT_RIGHT, DIGIT_EMPTY},
		{DIGIT_TOP, DIGIT_TOP_LEFT, DIGIT_TOP_RIGHT, DIGIT_MID, DIGIT_BOT_LEFT, DIGIT_BOT_RIGHT, DIGIT_BOT},
		{DIGIT_TOP, DIGIT_TOP_LEFT, DIGIT_TOP_RIGHT, DIGIT_MID, DIGIT_EMPTY, DIGIT_BOT_RIGHT, DIGIT_BOT},
	};
	return (init_tab(tab));
}

static void			draw_text(float offset_x, float offset_y, int nb)
{
	int			**tab;
	int			i;

	tab = tab_number();
	i = 0;
	while (i < 7)
	{
		if (tab[nb][i] == DIGIT_TOP)
			glRectf(-1.0f + offset_x, 1.0f + offset_y, -0.9f + offset_x, 0.99f + offset_y);
		else if (tab[nb][i] == DIGIT_TOP_LEFT)
			glRectf(-1.0f + offset_x, 1.0f + offset_y, -0.99f + offset_x, 0.9f + offset_y); 
		else if (tab[nb][i] == DIGIT_TOP_RIGHT)
			glRectf(-0.9f + offset_x, 1.0f + offset_y, -0.89f + offset_x, 0.9f + offset_y);
		else if (tab[nb][i] == DIGIT_MID)
			glRectf(-1.0f + offset_x, 0.9f + offset_y, -0.9f + offset_x, 0.89f + offset_y);
		else if (tab[nb][i] == DIGIT_BOT_LEFT)
			glRectf(-1.0f + offset_x, 0.9f + offset_y, -0.99f + offset_x, 0.8f + offset_y);
		else if (tab[nb][i] == DIGIT_BOT)
			glRectf(-1.0f + offset_x, 0.8f + offset_y, -0.89f + offset_x, 0.79f + offset_y);
		else if (tab[nb][i] == DIGIT_BOT_RIGHT)
			glRectf(-0.9f + offset_x, 0.9f + offset_y, -0.89f + offset_x, 0.8f + offset_y);
		i++;
	}
	glEnd(); 
}



int		draw_score(int n, float offset_x, float offset_y)
{
	if (n < INT_MAX)
	{
		if (n >= 0)
		{
			if (n >= 10)
			{
				draw_text(offset_x, offset_y, n % 10);
				offset_x = offset_x - 0.15;
				return (draw_score(n / 10, offset_x, -0.1f));
			}
			else
				draw_text(offset_x, offset_y, n);
		}
	}
	else if (n == INT_MAX)
		draw_text(offset_x, offset_y, INT_MAX);
	return (0);
}
