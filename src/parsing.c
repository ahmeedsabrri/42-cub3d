/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:36:30 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/13 05:48:35 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	if_condition(char c)
{
	if (c != 'N' && c != 'S' \
		&& c != 'E' && c != 'W' \
		&& c != 'F' && c != 'C' && c != '\n')
		return (1);
	return (0);
}

void	check_extension(char **av)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strrchr(av[1], '.');
	tmp2 = av[1];
	if (ft_strlen(tmp2) == ft_strlen(tmp))
		ft_error("Error :\nExtension Error\n");
	if (!tmp)
		ft_error("Error :\nExtentsion Error\n");
	if (ft_strcmp(tmp, ".cub") == 0)
		return ;
	else
		ft_error("Error :\nExtension Error\n");
}

int	dup_check_infos(char **str, char *line)
{
	if (*str)
		return (1);
	*str = ft_strdup(line);
	return (0);
}

int	get_textures(t_infos **infos, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "NO\t", 3))
	{
		if (dup_check_infos(&(*infos)->north, line))
			return (1);
	}
	else if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "SO\t", 3))
	{
		if (dup_check_infos(&(*infos)->south, line))
			return (1);
	}
	else if (!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "EA\t", 3))
	{
		if (dup_check_infos(&(*infos)->east, line))
			return (1);
	}
	else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "WE\t", 3))
	{
		if (dup_check_infos(&(*infos)->west, line))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	get_infos(char	**line, t_infos **infos, int fd)
{
	while (*line)
	{
		while (is_space(**line)) 
			(*line)++;
		if (!ft_strncmp(*line, "F ", 2) || !ft_strncmp(*line , "F\t", 2))
		{
			if (dup_check_infos(&(*infos)->floor, *line))
				return (1);
		}
		else if (!ft_strncmp(*line, "C ", 2) || !ft_strncmp(*line , "C\t", 2))
		{
			if (dup_check_infos(&(*infos)->ceiling, *line))
				return (1);
		}
		else if (**line == 'N' || **line == 'S' || **line == 'E' || **line == 'W')
		{
			if (get_textures(infos, *line))
				return (1);
		}
		else if (**line == '\n')
		{
			*line = get_next_line(fd);
			continue ;
		}
		else if ((*infos)->floor && (*infos)->ceiling && (*infos)->north \
			&& (*infos)->south && (*infos)->east && (*infos)->west)
				break;
		*line = get_next_line(fd);
	}
	return (0);
}

int	store_map(int fd, t_data **data, int count, char *line)
{
	int i;

	(*data)->map = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(*data)->map)
		return (ft_error("malloc error\n"), 1);
	while (line)
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (line[i] != '1' && line[i] != '0')
			line = get_next_line(fd);
		else
			break;
	}
	i = 0;
	while (line)
	{
		(*data)->map[i] = ft_strdup_n(line);
		i++;
		line = get_next_line(fd);
	}
	(*data)->map[i] = NULL;
	return (0);
}

int	check_store_map(char **av, char *line, int fd, t_data **data)
{
	int		count;

	count = 0;
	while (line)
	{
		while (line && is_space(*line))
			(line)++;
		if (*line && *line != '1' && *line != '0')
			return (1);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	store_map(fd, data, count, line);
	return (0);
}

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t  i;
    char    *src1;
    char    *dst1;
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

void    *ft_memset(void *b, int c, size_t len)
{
        size_t                  i;
        unsigned char   *ptr;

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
	int		i = 0;
	int width;

	width = width_size((*data)->map);
	tmp = malloc(sizeof(char) * width + 1);
	if(!tmp)
		return (1);
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

int	parsing(int ac, char **av, t_data *data)
{
	int		fd;
	char	*info_line;
	t_infos	*infos;

	(void)data;
	if (ac != 2)
		ft_error("Error: Should be one argument\n");
	check_extension(av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	info_line = get_next_line(fd);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (1);
	(infos->east = NULL, infos->west = NULL, infos->north = NULL);
	(infos->south = NULL, infos->floor = NULL, infos->ceiling = NULL);
	if (get_infos(&info_line, &infos, fd))
		return (ft_error("Informations Error\n"), 1);
	(data->infos = infos);
	if (check_infos(&infos, &data))
		return (ft_error("Head Infos Error\n"), 1);
	if (check_store_map(av, info_line,  fd, &data))
		return (ft_error("Map Error\n"), 1);
	if (check_map_valid(&data))
		return (ft_error("Map Not valid\n"), 1);
	if (resize_to_same_width(&data))
		return (1);
	return (0);
}
