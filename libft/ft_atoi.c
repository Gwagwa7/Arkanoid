/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 12:01:10 by mcassagn          #+#    #+#             */
/*   Updated: 2015/04/24 12:01:11 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int		nbr;
	int		sign;

	sign = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		sign = (*(str++) == '-' ? -sign : sign);
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + ((*(str++) - '0') * sign);
	return (nbr);
}