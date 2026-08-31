/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:54:12 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/08 18:56:11 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lendest;
	size_t	lensrc;

	i = 0;
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	if (size <= lendest)
		return ((size + lensrc));
	else
	{
		while (src[i] && i < (size - lendest - 1))
		{
			dest[lendest + i] = src[i];
			i++;
		}
	}
	dest[lendest + i] = '\0';
	return (lensrc + lendest);
}
