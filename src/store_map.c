/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:36:30 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/22 17:00:09 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	if_condition(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'F' && c != 'C'
		&& c != '\n')
		return (1);
	return (0);
}

int	store_map(int fd, t_data **data, int count, char *line)
{
	int	i;

	(*data)->map = (char **)ft_malloc(sizeof(char *) * (count + 1), 1);
	while (line)
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (line[i] != '1' && line[i] != '0')
			line = get_next_line(fd);
		else
			break ;
	}
	i = 0;
	while (line)
	{
		(*data)->map[i] = ft_strdup_n(line);
		i++;
		line = get_next_line(fd);
	}
	(*data)->map[i] = NULL;
	close(fd);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*src1;
	char	*dst1;

	i = 0;
	if (!src && !dst)
		return (NULL);
	src1 = (char *)src;
	dst1 = (char *)dst;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int	resize_to_same_width(t_data **data)
{
	char	*tmp;
	int		i;
	int		width;

	i = 0;
	width = width_size((*data)->map);
	tmp = ft_malloc(sizeof(char) * width + 1, 1);
	ft_memset(tmp, '1', width);
	tmp[width] = '\0';
	while ((*data)->map[i])
	{
		if (ft_strlen((*data)->map[i]) < (size_t)width)
		{
			ft_memcpy(tmp, (*data)->map[i], ft_strlen((*data)->map[i]));
			(*data)->map[i] = ft_strdup(tmp);
			ft_memset(tmp, '1', width);
		}
		i++;
	}
	return (0);
}
