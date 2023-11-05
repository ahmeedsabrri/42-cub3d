/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:55:10 by abberkac          #+#    #+#             */
/*   Updated: 2023/10/23 18:18:36 by abberkac         ###   ########.fr       */
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

int	count_word(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			n++;
		}
	}
	return (n);
}

int	word_len(char *s, char c)
{
	int	count;

	count = 0;
	while (*s && *s != c)
	{
		s++;
		count++;
	}
	return (count);
}

char	**ft_free(char **str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char			**str;
	unsigned int	i;
	unsigned int	count;
	unsigned int	start;

	if (!s)
		return (0);
	i = 0;
	start = 0;
	count = count_word(s, c);
	str = (char **)malloc(sizeof(*str) * (count + 1));
	if (!str)
		return (0);
	str[count] = NULL;
	while (i < count)
	{
		while (s[start] && s[start] == c)
			start++;
		str[i] = ft_substr(s, start, word_len(s + start, c));
		if (!str[i])
			return (ft_free(str, i));
		i++;
		start = start + word_len(s + start, c);
	}
	return (str);
}