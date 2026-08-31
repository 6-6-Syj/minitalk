/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 17:46:53 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 17:46:53 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*arr;

	arr = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	i = 0;
	if (arr == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		arr[i] = s[i];
		i++;
	}
	return (arr);
}
