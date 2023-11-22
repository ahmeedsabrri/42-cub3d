/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:42:41 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/22 16:58:26 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strncpy(char *dest, const char *src, int n)
{
	while (n > 0 && *src != '\0')
	{
		*dest++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}
	return (dest);
}

char	*ft_strndup(char *str, size_t n)
{
	size_t	length;
	char	*new_str;

	length = 0;
	while (length < n && str[length] != '\0')
		length++;
	new_str = (char *)ft_malloc(length + 1, 1);
	if (new_str)
	{
		ft_strncpy(new_str, str, length);
		new_str[length] = '\0';
	}
	return (new_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*new;
	int		len;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)ft_malloc(sizeof(char) * (len + 1), 1);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (is_space(*str))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	while (*str && *str != ',')
	{
		if (!is_space(*str) && *str != '\n')
			return (-1);
		str++;
	}
	if (result > 255)
		return (-1);
	return (result);
}

void	checking_condition(char line)
{
	if (line != 'F' && line != 'C' && line != 'N' && line != 'S' \
		&& line != 'E' && line != 'W' && line != '\n')
		return (ft_error("Head Infos Not Exist\n"));
}
