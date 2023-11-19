/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:15:32 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/19 18:09:51 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_height(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	ft_renderplayer1(t_data *data)
{
	double	mv;
	double	px;
	double	py;

	mv = data->player->side_direction * data->player->walkspeed;
	data->player->rotat_angle += data->player->turn_direct
		* data->player->turnspeed;
	px = data->player->px + cos(data->player->rotat_angle + M_PI_2) * mv;
	py = data->player->py + sin(data->player->rotat_angle + M_PI_2) * mv;
	if (!wall_hit(px, py, data))
	{
		data->player->px = px;
		data->player->py = py;
	}
}

void	ft_renderplayer(t_data *data)
{
	double	mv;
	double	px;
	double	py;

	mv = data->player->walk_direct * data->player->walkspeed;
	data->player->rotat_angle += data->player->turn_direct
		* data->player->turnspeed;
	px = data->player->px + cos(data->player->rotat_angle) * mv;
	py = data->player->py + sin(data->player->rotat_angle) * mv;
	if (!wall_hit(px, py, data))
	{
		data->player->px = px;
		data->player->py = py;
	}
}

double	check_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (M_PI);
	return (0);
}

void	get_player_pos(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (strchr("NEWS", data->map[y][x]))
			{
				data->player->px = ((x * TILE_SIZE) + (TILE_SIZE / 2));
				data->player->py = ((y * TILE_SIZE) + (TILE_SIZE / 2));
				data->player->rotat_angle = check_angle(data->map[y][x]);
			}
		}
	}
}
