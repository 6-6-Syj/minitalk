/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 13:05:29 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 13:05:29 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == 0)
		return ((char *) big);
	while (big[i] != '\0' && i < len)
	{
		while ((big[i + j] == little[j]))
		{
			j++;
			if (little[j] == '\0' && (i + j) <= len)
				return ((char *) &big[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
