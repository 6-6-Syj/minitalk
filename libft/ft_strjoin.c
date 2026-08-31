/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-13 11:32:37 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-13 11:32:37 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*temp_s;

	i = 0;
	temp_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (temp_s == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		temp_s[i] = (char) s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		temp_s[i + j] = (char) s2[j];
		j++;
	}
	temp_s[i + j] = '\0';
	return (temp_s);
}
