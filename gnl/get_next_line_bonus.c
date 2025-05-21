/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:40:55 by abkhefif          #+#    #+#             */
/*   Updated: 2025/01/20 12:42:00 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*process_buffer(char *temp, char *buffer)
{
	char	*tmp;

	if (!temp)
		temp = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(temp, buffer);
		free(temp);
		temp = tmp;
	}
	return (temp);
}

char	*read_line(int fd, char *temp)
{
	char	*buffer;
	int		bytes_read;

	if (temp && ft_strchr(temp, '\n'))
		return (temp);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = process_buffer(temp, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == -1)
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

char	*ft_getline(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	char		*temp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = (ft_getline(buffer[fd]));
	if (ft_strchr(buffer[fd], '\n'))
	{
		temp = ft_strdup(ft_strchr(buffer[fd], '\n') + 1);
		free(buffer[fd]);
		buffer[fd] = temp;
	}
	else
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
