/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 12:04:31 by mcassagn          #+#    #+#             */
/*   Updated: 2015/04/24 12:06:05 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	char		*ret;

	if ((ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (*s1)
			ret[i++] = *(s1++);
	}
	if (s2)
	{
		while (*s2)
			ret[i++] = *(s2++);
	}
	return (ret);
}

char	*ft_joinfree(char *s1, char *s2, int free_str)
{
	char *ret;

	ret = NULL;
	ret = ft_strjoin(s1, s2);
	if (free_str == 1 || free_str == 3)
	{
		if (s1)
			free(s1);
	}
	if (free_str == 2 || free_str == 3)
	{
		if (s2)
			free(s2);
	}
	return (ret);
}
