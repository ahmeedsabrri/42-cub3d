/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:13:59 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/23 15:51:07 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_infos(t_infos *infos)
{
	infos->east = NULL;
	infos->west = NULL;
	infos->north = NULL;
	infos->south = NULL;
	infos->floor = NULL;
	infos->ceiling = NULL;
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

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (ft_malloc(0, 1), exit(1));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
