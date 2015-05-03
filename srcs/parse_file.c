/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apantiez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 18:37:01 by apantiez          #+#    #+#             */
/*   Updated: 2015/05/02 18:39:02 by apantiez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "arkanoid.h"

static void			init_end_level(t_game *game)
{
	t_level			*lv;
	t_level			*lv_next;

	lv = game->levels;
	while (lv->next)
		lv = lv->next;
	lv_next = init_level();
	lv_next->prev = lv;
	lv->next = lv_next;
}

void				parse_file(t_game *game)
{
	DIR				*dir;
	struct dirent	*read_dir;
	int				fd;
	char			*path;

	dir = opendir("./levels");
	if (dir == NULL)
		return ;
	while ((read_dir = readdir(dir)))
	{
		if (read_dir->d_type == 8)
		{
			path = ft_strjoin("./levels/", read_dir->d_name);
			fd = open(path, O_RDONLY);
			if (fd != -1)
			{
				if (game->levels == NULL)
					game->levels = init_level();
				else
					init_end_level(game);
				parsing(fd, game);
			}
			free(path);
		}
	}
}
