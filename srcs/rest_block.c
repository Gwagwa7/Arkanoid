/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 22:06:14 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 22:06:42 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arkanoid.h>

int			rest_destuctible_block(t_game *game)
{
	t_block	*block;
	int		i;
	int		j;

	i = 0;
	while (i < game->level_width)
	{
		j = 0;
		while (j < game->level_height)
		{
			block = &(game->blocks[j][i]);
			if (block->type != BLOCK_IMMORTAL && block->type != BLOCK_EMPTY)
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
