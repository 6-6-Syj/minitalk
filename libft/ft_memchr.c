/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 11:46:20 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 11:46:20 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*temp_s;

	temp_s = (unsigned char *) s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if ((unsigned char) temp_s[i] == (unsigned char) c)
			return (&temp_s[i]);
		i++;
	}
	return (NULL);
}
