/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:03:52 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/18 10:11:35 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		return (ft_error("Information Error\n"), 1);
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

int	check_zeros_and_player(char **map, char plyr, int *i)
{
	int	j;

	j = 0;
	while (map[*i][j])
	{
		if (map[*i][j] == '0' && ((map[*i][j + 1] != '1' && map[*i][j \
					+ 1] != '0' && map[*i][j + 1] != plyr) || (map[*i][j \
					- 1] != '1' && map[*i][j - 1] != '0' && map[*i][j \
					- 1] != plyr) || (map[*i + 1][j] != '1' && map[*i \
					+ 1][j] != '0' && map[*i + 1][j] != plyr) || (map[*i \
					- 1][j] != '1' && map[*i - 1][j] != '0' && map[*i \
					- 1][j] != plyr)))
			return (1);
		else if (map[*i][j] == plyr && ((map[*i][j + 1] != '1' && map[*i][j
						+ 1] != '0') || (map[*i][j - 1] != '1' && map[*i][j
						- 1] != '0') || (map[*i + 1][j] != '1' && map[*i
						+ 1][j] != '0') || (map[*i - 1][j] != '1' && map[*i
						- 1][j] != '0')))
			return (1);
		j++;
	}
	return (0);
}
