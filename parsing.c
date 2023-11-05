/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:36:30 by abberkac          #+#    #+#             */
/*   Updated: 2023/10/24 02:37:37 by abberkac         ###   ########.fr       */
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

char	*read_map(int fd)
{
	int		check;
	char	*buf;
	char	*map;

	map = ft_strdup("");
	buf = NULL;
	check = 1;
	while (check > 0)
	{
		map = ft_strjoin(map, buf);
		buf = (char *)malloc(2);
		if (!buf)
			return (NULL);
		check = read(fd, buf, 1);
		buf[1] = '\0';
	}
	free(buf);
	return (map);
}

int spliting(char *file, t_map **map) {
    char *start = file;
    char *end = file;

    while (*end) {
        if (*end == '\n') {
            ft_add_data(map, ft_strndup(start, end - start), line);

            // Allocate memory for the newline character and add it to the linked list
            char *newline = (char *)malloc(2);
            if (newline) {
                newline[0] = *end;
                newline[1] = '\0';
                ft_add_data(map, newline, n_line);
            }

            start = end + 1; // Move the start position to the character after the newline.
        }
        end++;
    }

    // Handle the last line (if any) without a trailing newline
    if (start != end) {
        ft_add_data(map, ft_strndup(start, end - start), line);
    }

    return 0;
}



int	parsing(int ac, char **av, t_data *data)
{
	int		fd;
	char	*full_file;
	// char	**splited;
	t_map	*map;

	map = NULL;
	(void)data;
    if (ac != 2)
		ft_error("Error :\nShould be one argument\n");
    check_extension(av);
    fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	full_file = read_map(fd);
	if (!full_file)
		return (1);
	spliting(full_file, &map);
	while (map)
	{
		printf("%s\n", map->line);
		map = map->next;
	}
	
	return (0);
}
