/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:42:41 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/12 03:02:14 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int     ft_isdigit(int c)
{
        if (c >= '0' && c <= '9')
                return (1);
        return (0);
}

char    *ft_strrchr(const char *s, int c)
{
        unsigned int    i;

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
	exit (1);
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

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!new)
		return (NULL);
	while (*s1)
		new[i++] = *s1++;
	new[i] = '\0';
	return (new);
}

char	*ft_strdup_n(const char *s1)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!new)
		return (NULL);
	while (*s1 != '\0' && *s1 != '\n')
		new[i++] = *s1++;
	new[i] = '\0';
	return (new);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	size_t				j;

	i = 0;
	j = 0;
	if (!n)
		return (0);
	while ((s1[i] && s2[j] && (s1[i] == s2[j]) && i < (n - 1)))
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}


char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len)
		len = s_len - start;
	i = -1;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (++i < len)
		sub[i] = s[start + i];
	sub[i] = '\0';
	return (sub);
}

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
	new_str = (char *)malloc(length + 1);
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
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}

int     ft_atoi(const char *str)
{
	int result;

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
