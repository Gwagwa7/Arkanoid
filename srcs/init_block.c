/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apantiez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 18:06:20 by apantiez          #+#    #+#             */
/*   Updated: 2015/05/03 20:47:32 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "arkanoid.h"

t_block		**init_block(int w, int h)
{
	t_block	**block;
	int		i;

	i = 0;
	block = (t_block **)malloc(sizeof(t_block *) * h);
	while (i < h)
	{
		block[i] = (t_block *)malloc(sizeof(t_block) * w);
		i++;
	}
	return (block);
}

void		set_life(t_block *block)
{
	if (block->type == BLOCK_EASY)
		block->life = 1;
	else if (block->type == BLOCK_MEDIUM)
		block->life = 2;
	else if (block->type == BLOCK_HARD)
		block->life = 3;
}

void		add_block(t_block *block, char *line, int i, int nb_line)
{
	block->pos.x = i;
	block->pos.y = nb_line;
	if (line[i] == '1')
		block->type = BLOCK_EASY;
	else if (line[i] == '2')
		block->type = BLOCK_MEDIUM;
	else if (line[i] == '3')
		block->type = BLOCK_HARD;
	else if (line[i] == '4')
		block->type = BLOCK_IMMORTAL;
	else if (line[i] == '5')
		block->type = BLOCK_BONUS;
	else
	{
		if (line[i] == '0')
			block->type = BLOCK_EMPTY;
		else
		{
			ft_printf("unexpected character x = %d y = %d, ", i, nb_line);
			ft_printf("it is considered empty block\n");
		}
	}
	block->bonus = NULL;
	set_life(block);
}

int			get_block(t_level *lv, char *line, int nb_line)
{
	int		i;

	i = 0;
	if ((int)ft_strlen(line) != lv->width)
		return (-1);
	if (lv->blocks == NULL)
		lv->blocks = init_block(lv->width, lv->height);
	while (line[i])
	{
		add_block(&(lv->blocks[nb_line][i]), line, i, nb_line);
		i++;
	}
	return (0);
}
