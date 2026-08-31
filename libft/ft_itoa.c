/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-21 12:57:14 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-21 12:57:14 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	size_t	len;
	char	*arr;

	nb = n;
	len = int_len(nb) - 1;
	arr = ft_calloc((len + 2), sizeof(char));
	if (!arr)
		return (NULL);
	arr[0] = '0';
	if (nb < 0)
		nb = -nb;
	while (nb != 0)
	{
		arr[len] = ((nb % 10) + 48);
		nb = nb / 10;
		len--;
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}
