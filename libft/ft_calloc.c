/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 17:08:23 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 17:08:23 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*arr;

	i = 0;
	if ((size == 0 || nmemb == 0))
		return (malloc(0));
	if (nmemb * size / nmemb != size)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (arr);
	while (i < nmemb * size)
	{
		((unsigned char *) arr)[i] = 0;
		i++;
	}
	return (arr);
}
