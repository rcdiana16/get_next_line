/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:23:14 by diana             #+#    #+#             */
/*   Updated: 2024/12/08 11:15:21 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#ifndef MAX_FD
# define MAX_FD 1024
#endif

static char	*ft_strchr(char *s1, int c)
{
	if (!s1)
		return (NULL);
	while (*s1)
	{
		if (*s1 == (char) c)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}

static ssize_t	read_into_buffer(int fd, char **buffer)
{
	char	tmp[BUFFER_SIZE + 1];
	char	*new_buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!*buffer)
		*buffer = NULL;
	while (!ft_strchr(*buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		tmp[bytes_read] = '\0';
		new_buffer = ft_strjoin_free(*buffer, tmp);
		if (!new_buffer)
			return (-1);
		*buffer = new_buffer;
	}
	return (bytes_read);
}

static char	*get_line_in_buffer(char *buffer)
{
	int		i;
	char	*line;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*trim_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_into_buffer(fd, &buffer[fd]);
	if (bytes_read < 0 || (!bytes_read && (!buffer[fd] || !buffer[fd][0])))
	{
		if (buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	line = get_line_in_buffer(buffer[fd]);
	buffer[fd] = trim_buffer(buffer[fd]);
	return (line);
}
