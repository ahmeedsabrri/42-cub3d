/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:12:37 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/18 10:15:40 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	init_vars(t_varaible *var, int flag)
{
	if (flag == 0)
	{
		var->i = 0;
		var->idx = 0;
		var->c = 0;
		var->count = 0;
	}
	else if (flag == 1)
	{
		free(var->tmp);
		var->count = 0;
		var->idx = var->i + 1;
		var->c++;
	}
}

int	condition(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (0);
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	return (1);
}

int	existence_condition(t_infos *infos)
{
	return (infos->floor && infos->ceiling && infos->north && infos->south
		&& infos->east && infos->west);
}
