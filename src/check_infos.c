/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:49:40 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/18 15:58:56 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	store_valid_infos(char **str, int flag)
{
	char	*tmp;

	if (!*str)
		return (1);
	while (*str && !is_space(**str))
		(*str)++;
	while (*str && is_space(**str))
		(*str)++;
	if (**str == '\n')
		return (1);
	if (!flag)
		tmp = ft_strdup_n(*str);
	else
		tmp = ft_strdup(*str);
	if (tmp == NULL)
		return (1);
	*str = tmp;
	return (0);
}

int	extract_rgb_floor(t_floor **floor, char *color)
{
	t_varaible	var;

	init_vars(&var, 0);
	while (color[var.i])
	{
		if (ft_isdigit(color[var.i]))
			var.count++;
		else if (color[var.i] == ',' || color[var.i] == '\n')
		{
			if (var.count > 3 || !var.count || var.c > 2)
				return (1);
			var.tmp = ft_strndup(color + var.idx, var.i);
			if (var.c == 0)
				(*floor)->r = ft_atoi(var.tmp);
			else if (var.c == 1)
				(*floor)->g = ft_atoi(var.tmp);
			else if (var.c == 2)
				(*floor)->b = ft_atoi(var.tmp);
			if ((*floor)->r < 0 || (*floor)->g < 0 || (*floor)->b < 0)
				return (1);
			init_vars(&var, 1);
		}
		var.i++;
	}
	return (0);
}

int	extract_rgb_ceiling(t_ceiling **ceiling, char *color)
{
	t_varaible	var;

	init_vars(&var, 0);
	while (color[var.i])
	{
		if (ft_isdigit(color[var.i]))
			var.count++;
		else if (color[var.i] == ',' || color[var.i] == '\n')
		{
			if (var.count > 3 || !var.count || var.c > 2)
				return (1);
			var.tmp = ft_strndup(color + var.idx, var.i);
			if (var.c == 0)
				(*ceiling)->r = ft_atoi(var.tmp);
			else if (var.c == 1)
				(*ceiling)->g = ft_atoi(var.tmp);
			else if (var.c == 2)
				(*ceiling)->b = ft_atoi(var.tmp);
			if ((*ceiling)->r < 0 || (*ceiling)->g < 0 || (*ceiling)->b < 0)
				return (1);
			init_vars(&var, 1);
		}
		var.i++;
	}
	return (0);
}

int	check_colors_valid(char *color)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' \
			&& color[i] != '\n' && !is_space(color[i]))
			return (1);
		if (color[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (1);
	return (0);
}

int	fill_rgb_colors(t_floor **floor, t_ceiling **ceiling, char *fl, char *cl)
{
	*floor = malloc(sizeof(t_floor));
	if (!*floor)
		return (1);
	(*floor)->r = 0;
	(*floor)->g = 0;
	(*floor)->b = 0;
	if (extract_rgb_floor(floor, fl))
		return (1);
	*ceiling = malloc(sizeof(t_ceiling));
	if (!*ceiling)
		return (1);
	(*ceiling)->r = 0;
	(*ceiling)->g = 0;
	(*ceiling)->b = 0;
	if (extract_rgb_ceiling(ceiling, cl))
		return (1);
	return (0);
}
