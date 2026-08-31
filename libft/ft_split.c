/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:20:56 by jmagand           #+#    #+#             */
/*   Updated: 2024/11/19 19:01:15 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	word;

	i = 0;
	count = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && word == 0)
		{
			count++;
			word = 1;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

static void	to_free(char **arr, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*fill(char *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**cut(char **arr, char *s, char c, size_t i)
{
	size_t	j;
	int		word;

	j = 0;
	word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && word < 0)
			word = i;
		else if (((s[i] == c || i == ft_strlen(s))) && word >= 0)
		{
			arr[j] = fill((char *) s, word, i);
			if (!(arr[j]))
			{
				to_free(arr, j);
				return (NULL);
			}
			word = -1;
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;

	i = 0;
	if (!s)
	{
		arr = ft_calloc(1, 1);
		return (arr);
	}
	arr = malloc((count_words((char *) s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (cut(arr, (char *) s, c, i));
}
