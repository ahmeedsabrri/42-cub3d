/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:43:51 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/18 15:58:45 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_first_last_walls(t_data **data)
{
	int		i;
	int		last;
	t_data	*crr;

	i = 0;
	last = 0;
	crr = *data;
	while (crr->map[0][i])
	{
		if (!is_space(crr->map[0][i]) && crr->map[0][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (crr->map[i])
		i++;
	last = i - 1;
	i = 0;
	while (crr->map[last][i])
	{
		if (!is_space(crr->map[last][i]) && crr->map[last][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_walls(t_data **data)
{
	int	i;
	int	j;

	i = 0;
	if (check_first_last_walls(data))
		return (1);
	while ((*data)->map[i])
	{
		j = 0;
		while (is_space((*data)->map[i][j]))
			j++;
		if ((*data)->map[i][j] != '1' ||
			((*data)->map[i][ft_strlen((*data)->map[i]) - 1] != '1'))
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_chars(t_data **data)
{
	t_varaible	var;

	init_vars(&var, 0);
	while ((*data)->map[var.i])
	{
		var.idx = 0;
		while ((*data)->map[var.i][var.idx])
		{
			if (condition((*data)->map[var.i][var.idx]))
				return (1);
			if ((*data)->map[var.i][var.idx] == 'N' \
				|| (*data)->map[var.i][var.idx] == 'E' \
				|| (*data)->map[var.i][var.idx] == 'W' \
				|| (*data)->map[var.i][var.idx] == 'S')
			{
				(*data)->plyr = (*data)->map[var.i][var.idx];
				var.count++;
			}
			var.idx++;
		}
		var.i++;
	}
	if (var.count != 1)
		return (1);
	return (0);
}

int	check_wall_around_chars(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->map[i])
	{
		if (check_zeros_and_player((*data)->map, (*data)->plyr, &i))
			return (1);
		i++;
	}
	return (0);
}

int	check_map_valid(t_data **data)
{
	if (check_walls(data))
		return (1);
	if (check_valid_chars(data))
		return (1);
	if (check_wall_around_chars(data))
		return (1);
	return (0);
}
