/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 12:03:28 by mcassagn          #+#    #+#             */
/*   Updated: 2015/04/24 12:06:04 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_puterr(char *s)
{
	if (s)
		write (2, s, ft_strlen(s));
}

void	ft_errorexit(char *s)
{
	if (s)
		write (2, s, ft_strlen(s));
	write (2, "\n", 1);
	_Exit(-1);
}
