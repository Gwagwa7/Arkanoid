/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_levels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apantiez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 18:08:56 by apantiez          #+#    #+#             */
/*   Updated: 2015/05/02 18:32:02 by apantiez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "arkanoid.h"

t_level		*init_level(void)
{
	t_level	*lv;

	lv = (t_level *)malloc(sizeof(t_level));
	lv->height = 0;
	lv->width = 0;
	lv->blocks = NULL;
	lv->next = NULL;
	lv->prev = NULL;
	return (lv);
}

int			sav_name(t_level *lv, char *line)
{
	char	*name;

	name = ft_strdup(line);
	lv->name = name;
	return (0);
}

int			sav_height(t_level *lv, char *line)
{
	int		nb;

	nb = ft_atoi(line);
	if (nb <= 0)
		return (-1);
	else
		lv->height = nb;
	return (0);
}

int			sav_width(t_level *lv, char *line)
{
	int		nb;

	nb = ft_atoi(line);
	if (nb <= 0)
		return (-1);
	else
		lv->width = nb;
	return (0);
}
