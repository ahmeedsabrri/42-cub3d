/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 18:09:51 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_player(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 360)
	{
		dda(data, (200 / 2), (200 / 2), (200 / 2) + (cos(i * PI / 180) * 10), \
			(200 / 2) + (sin(i * PI / 180) * 10), ft_pixel(1, 85, 172, 200));
	}
	dda(data, (200 / 2), (200 / 2), (200 / 2) \
		+ (cos(data->player->rotat_angle) * 30), (200 / 2) \
		+ (sin(data->player->rotat_angle) * 30), ft_pixel(1, 85, 172, 200));
}

void	draw_minimap(t_data *data, t_m_map m_map)
{
	m_map.xstart = (int)(m_map.xstart / TILE_SIZE);
	m_map.ystart = (int)(m_map.ystart / TILE_SIZE);
	if (m_map.ystart < 0 || m_map.xstart < 0 || m_map.ystart > 200 \
		|| m_map.xstart > 200)
	{
		mlx_put_pixel(data->image_win, m_map.i, m_map.j, \
		ft_pixel(0, 0, 0, 255));
		return ;
	}
	if (wall_hit(m_map.xstart * TILE_SIZE, m_map.ystart * TILE_SIZE, data))
		mlx_put_pixel(data->image_win, m_map.j, m_map.i, \
		ft_pixel(106, 50, 159, 255));
	else
		mlx_put_pixel(data->image_win, m_map.j, m_map.i, \
		ft_pixel(68, 68, 68, 255));
	if (m_map.distance > 95)
		mlx_put_pixel(data->image_win, m_map.j, m_map.i, \
		ft_pixel(120, 120, 120, 255));
}

void	renderminimap(t_data *data)
{
	t_m_map	m_map;

	m_map.xstart = (data->player->px) - ((200) / 2.0);
	m_map.ystart = (data->player->py) - ((200) / 2.0);
	m_map.i = -1;
	while (++m_map.i < ((200)))
	{
		m_map.xstart = (data->player->px) - ((200) / 2.0);
		m_map.j = -1;
		m_map.distance = 0;
		while (++m_map.j < ((200)))
		{
			m_map.distance = sqrt(pow(m_map.j - 100, 2) \
			+ pow(m_map.i - 100, 2));
			if (m_map.distance < 100)
				draw_minimap(data, m_map);
			m_map.xstart++;
		}
		m_map.ystart++;
	}
	draw_player(data);
}

int	width_size(char **str)
{
	size_t	width;
	int		i;

	i = 1;
	width = ft_strlen(str[0]);
	while (str[i])
	{
		if (ft_strlen(str[i]) > width)
			width = ft_strlen(str[i]);
		i++;
	}
	return ((int)width);
}
// end of file
