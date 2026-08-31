/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-09 13:09:57 by jmagand           #+#    #+#             */
/*   Updated: 2024-12-09 13:09:57 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_gnl_bzero(void *s)
{
	unsigned char	*temp_s;
	size_t			i;

	temp_s = (unsigned char *)s;
	i = 0;
	while (temp_s[i])
	{
		temp_s[i] = 0;
		i++;
	}
}

static char	*ft_gnl_strjoin(char *s1, char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	res = malloc(ft_strlen(s1) + len + 1);
	if (!res)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

static char	*handle_eof(char *line, char *buffer, ssize_t read_bytes)
{
	if (line[0] == '\0' || read_bytes == -1)
	{
		free(line);
		ft_gnl_bzero(buffer);
		return (NULL);
	}
	return (line);
}

static ssize_t	set_line(char *buffer, char **line)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	*line = ft_gnl_strjoin(*line, buffer, i);
	if (!*line)
		return (-1);
	if (buffer[i - 1] == '\n')
	{
		ft_memmove(buffer, buffer + i, ft_strlen(buffer + i) + 1);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		read_bytes;

	line = NULL;
	if (fd > FD_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		if (!buffer[0])
		{
			read_bytes = read(fd, buffer, BUFFER_SIZE);
			if (read_bytes <= 0)
				return (handle_eof(line, buffer, read_bytes));
			buffer[read_bytes] = '\0';
		}
		if (set_line(buffer, &line))
			return (line);
		ft_gnl_bzero(buffer);
	}
}

// int	main(void)
// {
// #include <fcntl.h>
// #include <stdio.h>
// #include "get_next_line.h"

// 	int fd = open("text.txt", O_RDONLY);
// 	char *str;

// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		ft_printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 		ft_printf("________________\n");
// 	}
// 	str = get_next_line(fd);
// 	ft_printf("%s", str);
// 	free(str);
// 	close(fd);
// }
