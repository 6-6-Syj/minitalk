/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 11:16:30 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-12 11:16:30 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	i = 0;
	temp_s1 = (unsigned char *) s1;
	temp_s2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && temp_s1[i] == temp_s2[i] && temp_s1[i] != '\0'
		&& temp_s2[i] != '\0')
		i++;
	return (temp_s1[i] - temp_s2[i]);
}
