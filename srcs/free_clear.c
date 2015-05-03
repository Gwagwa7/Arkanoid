/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apantiez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 18:11:30 by apantiez          #+#    #+#             */
/*   Updated: 2015/05/02 18:21:36 by apantiez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "arkanoid.h"

void		clear_last(t_level *lv, t_game *game)
{
	if (lv->prev != NULL)
	{
		lv->prev->next = NULL;
		free(lv);
	}
	else
	{
		free(lv);
		game->levels = NULL;
	}
}

void		free_block(t_level *lv)
{
	t_block **block;
	int		i;

	block = lv->blocks;
	i = 0;
	while (i < lv->height)
	{
		free(block[i]);
		i++;
	}
	free(lv->blocks);
}
