/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:57:51 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/22 17:04:25 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*read_line(int fd, char *result)
{
	char	*buffer;
	int		byte_readed;

	buffer = ft_malloc(BUFFER_SIZE + 1 * sizeof(char), 1);
	byte_readed = 1;
	while (byte_readed && !ft_strchr(result, '\n'))
	{
		byte_readed = read(fd, buffer, BUFFER_SIZE);
		if (byte_readed < 0)
			return (NULL);
		buffer[byte_readed] = '\0';
		result = strjoin(result, buffer);
	}
	return (result);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_malloc((i + 2) * sizeof(char), 1);
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
	{
		line[j] = buffer[j];
		j++;
	}
	if (buffer[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_get_next(char *buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (NULL);
	rest = ft_malloc((ft_strlen(buffer) - i + 1) * sizeof(char), 1);
	i++;
	j = 0;
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	line = ft_get_line(buffer);
	buffer = ft_get_next(buffer);
	return (line);
}
