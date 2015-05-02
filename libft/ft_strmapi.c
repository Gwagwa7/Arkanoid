/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 12:04:45 by mcassagn          #+#    #+#             */
/*   Updated: 2015/04/24 12:06:05 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned i, char))
{
	int		i;
	char	*str;

	i = 0;
	if (s && f)
	{
		str = ft_memalloc(ft_strlen((char *)s) + 1);
		if (str)
		{
			while (s[i] != '\0')
			{
				str[i] = f(i, s[i]);
				i++;
			}
			return (str);
		}
	}
	return (NULL);
}
