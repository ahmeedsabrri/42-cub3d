/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:01:44 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/22 16:57:30 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)ft_malloc(1 * sizeof(char), 1);
		s1[0] = '\0';
	}
	result = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!s2)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c && *s)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
