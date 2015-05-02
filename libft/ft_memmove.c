/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 12:02:56 by mcassagn          #+#    #+#             */
/*   Updated: 2015/04/24 12:06:04 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!(s1 > s2 && s2 + n > s1))
		ft_memcpy(s1, s2, n);
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			*((char *)s1 + i) = *((char *)s2 + i);
		}
	}
	return (s1);
}
