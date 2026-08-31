/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:54:03 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/08 18:24:48 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest1;
	unsigned char	*src1;

	i = 0;
	dest1 = (unsigned char *) dest;
	src1 = (unsigned char *) src;
	if (dest1 == NULL && src1 == NULL)
		return (dest);
	if (dest1 > src1)
	{
		while (n-- > 0)
			dest1[n] = src1[n];
	}
	else
	{
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dest);
}
