/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-13 15:32:15 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-13 15:32:15 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*arr;

	i = 0;
	len = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	arr = ft_calloc((len + 1), sizeof(char));
	if (arr == NULL)
		return (NULL);
	while (i < len)
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	return (arr);
}
