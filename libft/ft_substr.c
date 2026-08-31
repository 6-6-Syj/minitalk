/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 18:00:22 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 18:00:22 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*temp_s;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	temp_s = ft_calloc(len + 1, sizeof(char));
	if (temp_s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		temp_s[i] = s[start + i];
		i++;
	}
	return (temp_s);
}
