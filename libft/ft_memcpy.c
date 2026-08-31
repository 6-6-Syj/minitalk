/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:54:01 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/08 18:50:29 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	i = 0;
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (temp_dest == NULL && temp_src == NULL)
		return (temp_dest);
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (temp_dest);
}
