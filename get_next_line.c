/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:07:04 by diana             #+#    #+#             */
/*   Updated: 2024/11/25 22:52:23 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	return (NULL);
}

static char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static char	*set_line(char *line_buffer)
{
	char *left_c;
	ssize_t i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	left_c = ft_substr(line_buffer, i, ft_strlen(line_buffer) - i);
	if (!left_c)
		return (NULL);
	line_buffer[i] = 0;
	return (left_c);
}

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free (tmp);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return left_c;
}

char	*get_next_line(int fd)
{
	static char *left_c;
	char	*buffer;
	char	*line_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line_buffer = fill_line_buffer(fd, left_c, buffer);
	free (buffer);
	if (!line_buffer)
	{
		free(left_c);
		left_c = NULL;
		return (NULL);
	}
	left_c = set_line(line_buffer);
	if (!left_c)
	{
		free(line_buffer);
		return (NULL);
	}
	return (line_buffer);
}
