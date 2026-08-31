/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:54:21 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/08 18:55:39 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	size;
	char	temp_c;

	temp_c = (char) c;
	size = ft_strlen(str);
	while (size != 0)
	{
		if (str[size] == temp_c)
			return ((char *) &str[size]);
		size--;
	}
	if (str[size] == temp_c)
		return ((char *) &str[size]);
	return (NULL);
}
