/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 01:33:47 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/22 16:56:31 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_store_map(char **av, char *line, int fd, t_data **data)
{
	int	count;

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

int	check_infos(t_infos **infos, t_data **data)
{
	t_floor		*floor;
	t_ceiling	*ceiling;

	floor = NULL;
	ceiling = NULL;
	if (store_valid_infos(&(*infos)->north, 0) \
		|| store_valid_infos(&(*infos)->south, 0) \
		|| store_valid_infos(&(*infos)->east, 0) \
		|| store_valid_infos(&(*infos)->west, 0) \
		|| store_valid_infos(&(*infos)->floor, 1) \
		|| store_valid_infos(&(*infos)->ceiling, 1) \
		|| check_colors_valid((*infos)->floor) \
		|| check_colors_valid((*infos)->ceiling))
		return (1);
	if (fill_rgb_colors(&floor, &ceiling, (*infos)->floor, (*infos)->ceiling))
		return (1);
	(*data)->floor = floor;
	(*data)->ceiling = ceiling;
	return (0);
}

int	get_infos(char **line, t_infos **infos, int fd)
{
	while (*line)
	{
		while (is_space(**line))
			(*line)++;
		if (!ft_strncmp(*line, "F ", 2) || !ft_strncmp(*line, "F\t", 2))
			dup_check_infos(&(*infos)->floor, *line);
		else if (!ft_strncmp(*line, "C ", 2) || !ft_strncmp(*line, "C\t", 2))
			dup_check_infos(&(*infos)->ceiling, *line);
		else if (**line == 'N' || **line == 'S' || **line == 'E' \
				|| **line == 'W')
		{
			if (get_textures(infos, *line))
				return (1);
		}
		else if (**line == '\n')
		{
			*line = get_next_line(fd);
			continue ;
		}
		else if (existence_condition(*infos))
			break ;
		checking_condition(**line);
		*line = get_next_line(fd);
	}
	return (0);
}

int	parsing(char **av, t_data *data)
{
	int		fd;
	char	*info_line;
	t_infos	*infos;

	check_extension(av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("Can't Opening The Map File\n"), 1);
	info_line = get_next_line(fd);
	infos = ft_malloc(sizeof(t_infos), 1);
	init_infos(infos);
	if (get_infos(&info_line, &infos, fd))
		return (ft_error("Informations Error\n"), 1);
	data->infos = infos;
	if (check_infos(&infos, &data))
		return (ft_error("Head Infos Error\n"), 1);
	if (check_store_map(av, info_line, fd, &data))
		return (ft_error("Map Error\n"), 1);
	if (check_map_valid(&data))
		return (ft_error("Map Not valid\n"), 1);
	if (resize_to_same_width(&data))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_player	*player;

	if (ac != 2)
		ft_error("Error: Should be one argument\n");
	data = (t_data *)ft_malloc(sizeof(t_data), 1);
	player = (t_player *)ft_malloc(sizeof(t_player), 1);
	if (!player || parsing(av, data))
		return (ft_malloc(0, 0), 2);
	data->width = width_size(data->map);
	data->height = get_height(data->map);
	player->rotat_angle = PI / 2;
	player->side_direction = 0;
	player->walk_direct = 0;
	player->turn_direct = 0;
	player->walkspeed = 5;
	player->turnspeed = 3.00 * (M_PI / 180.0);
	data->player = player;
	init(data);
	ft_malloc(0, 2);
	return (0);
}
