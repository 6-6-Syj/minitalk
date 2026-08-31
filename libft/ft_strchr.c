/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:54:08 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/08 18:52:08 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	temp_c;

	i = 0;
	temp_c = (char) c;
	while (str[i])
	{
		if (str[i] == temp_c)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == temp_c)
		return ((char *) &str[i]);
	return (NULL);
}
