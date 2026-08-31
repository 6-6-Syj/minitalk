/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:54:05 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/08 18:56:35 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp_s;

	i = 0;
	temp_s = (unsigned char *) s;
	while (i < n)
	{
		temp_s[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
