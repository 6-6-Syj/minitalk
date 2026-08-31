/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 14:55:46 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 14:55:46 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	long	nb;
	long	temp_nb;

	i = 0;
	nb = 0;
	temp_nb = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			temp_nb *= -1;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		nb *= 10;
		nb += nptr[i] - '0';
		i++;
	}
	return (temp_nb * nb);
}
