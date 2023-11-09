/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:36:30 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/09 03:50:32 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return(exit(1));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	size_t				j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;

	i = ft_strlen(s);
	while (i)
		if (s[i--] == (char)c)
			return (&((char *)s)[i + 1]);
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	return (NULL);
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

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	check_infos(char **str, char *line)
{
	if (*str)
		return (1);
	*str = ft_strdup(line);
	return (0);
}

int	get_textures(t_infos **infos, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (check_infos(&(*infos)->north, line))
			return (1);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (check_infos(&(*infos)->south, line))
			return (1);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (check_infos(&(*infos)->east, line))
			return (1);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (check_infos(&(*infos)->west, line))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	get_infos(char	*line, t_infos **infos, int fd)
{

	while (line)
	{
		while (is_space(*line)) 
			line++;
		if (*line == 'F')
		{
			if (check_infos(&(*infos)->floor, line))
				return (1);
		}
		else if (*line == 'C')
		{
			if (check_infos(&(*infos)->ceiling, line))
				return (1);
		}
		else if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
		{
			if (get_textures(infos, line))
				return (1);
		}
		else if (*line != '\n' && (!(*infos)->floor || !(*infos)->ceiling || !(*infos)->north
			|| !(*infos)->south || !(*infos)->east || !(*infos)->west))
			return (1);
		line = get_next_line(fd);
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
		ft_error("Error:\nShould be one argument\n");
	check_extension(av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	info_line = get_next_line(fd);
	while (info_line && info_line[0] == '\n')
		info_line = get_next_line(fd);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (1);
	infos->east = NULL;
	infos->west = NULL;
	infos->north = NULL;
	infos->south = NULL;
	infos->floor = NULL;
	infos->ceiling = NULL;
	if (get_infos(info_line, &infos, fd))
		return (1);
	printf("%s", infos->floor);
	printf("%s", infos->ceiling);
	printf("%s", infos->north);
	printf("%s", infos->west);
	printf("%s", infos->east);
	printf("%s", infos->south);
	return (0);
}
