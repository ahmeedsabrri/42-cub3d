/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:42:41 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/09 03:46:46 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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