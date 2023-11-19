/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 14:21:10 by abberkac         ###   ########.fr       */
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
		+ (cos(data->player->rotationAngle) * 30), (200 / 2) \
		+ (sin(data->player->rotationAngle) * 30), ft_pixel(1, 85, 172, 200));
}

void	draw_minimap(t_data *data, double xstart, double ystart, int i, int j,
		double distance)
{
	xstart = (int)(xstart / Tile_size);
	ystart = (int)(ystart / Tile_size);
	if (ystart < 0 || xstart < 0 || ystart > 200 || xstart > 200)
	{
		mlx_put_pixel(data->image_win, i, j, ft_pixel(0, 0, 0, 255));
		return ;
	}
	if (wall_hit(xstart * Tile_size, ystart * Tile_size, data))
		mlx_put_pixel(data->image_win, j, i, ft_pixel(106, 50, 159, 255));
	else
		mlx_put_pixel(data->image_win, j, i, ft_pixel(68, 68, 68, 255));
	if (distance > 95)
		mlx_put_pixel(data->image_win, j, i, ft_pixel(120, 120, 120, 255));
}

void	renderminimap(t_data *data)
{
	double	xstart;
	double	ystart;
	double	distance;
	int		i;
	int		j;

	xstart = (data->player->px) - ((200) / 2.0);
	ystart = (data->player->py) - ((200) / 2.0);
	i = -1;
	while (++i < ((200)))
	{
		xstart = (data->player->px) - ((200) / 2.0);
		j = -1;
		distance = 0;
		while (++j < ((200)))
		{
			distance = sqrt(pow(j - 100, 2) + pow(i - 100, 2));
			if (distance < 100)
				draw_minimap(data, xstart, ystart, i, j, distance);
			xstart++;
		}
		ystart++;
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
