/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apantiez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 18:32:29 by apantiez          #+#    #+#             */
/*   Updated: 2015/05/02 18:36:01 by apantiez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "arkanoid.h"

static int	check_parsing(t_level *lv, char *line, int nb_line)
{
	if (nb_line > 3)
	{
		if ((get_block(lv, line, (nb_line - 4))) == -1)
			return (2);
	}
	else if (nb_line == 1)
		sav_name(lv, line);
	else if (nb_line == 2)
	{
		if (sav_height(lv, line) == -1)
			return (1);
	}
	else if (nb_line == 3)
	{
		if (sav_width(lv, line) == -1)
			return (1);
	}
	return (0);
}

void		parsing(int fd, t_game *game)
{
	char	*line;
	int		nb_line;
	int		error;
	t_level	*lv;

	nb_line = 1;
	error = 0;
	line = NULL;
	lv = game->levels;
	while (lv->next)
		lv = lv->next;
	while ((get_next_line(fd, &line)) > 0)
	{
		if (line[0] == EOF || line[0] == '\0')
			break ;
		if (check_parsing(lv, line, nb_line) != 0)
			break ;
		nb_line++;
	}
	if ((error == 2) && (lv->blocks != NULL))
		free_block(lv);
	if (((nb_line - 1) != (lv->height + 3)) || error > 0)
		clear_last(lv, game);
}
