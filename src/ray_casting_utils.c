/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:26:48 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 18:11:43 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	ft_fabs(double dx, double dy)
{
	if (fabs(dx) > fabs(dy))
		return (fabs(dx));
	else
		return (fabs(dy));
}

void	dda(t_data *data, double x1, double y1, double x2, double y2, int color)
{
	t_dda	dda;

	dda.dx = x2 - x1;
	dda.dy = y2 - y1;
	dda.i = 0;
	dda.steps = fmax(fabs(dda.dx), fabs(dda.dy));
	if (dda.steps == 0)
	{
		mlx_put_pixel(data->image_win, round(x1), round(y1), color);
		return ;
	}
	dda.x_increment = dda.dx / dda.steps;
	dda.y_increment = dda.dy / dda.steps;
	while (dda.i <= dda.steps)
	{
		if ((x1) > WIDTH || (x1) < 0 || (y1) < 0 || (y1) > HEIGHT)
			return ;
		mlx_put_pixel(data->image_win, round(x1), round(y1), color);
		x1 += dda.x_increment;
		y1 += dda.y_increment;
		dda.i++;
	}
}

int	angle_left_or_right(double angle)
{
	if (angle < (M_PI / 2) || angle > ((3 * M_PI) / 2))
		return (1);
	return (0);
}

int	angle_up_or_down(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int	wall_hit(double px, double py, t_data *data)
{
	int	x;
	int	y;

	x = (px / TILE_SIZE);
	y = (py / TILE_SIZE);
	if (x > data->width || x < 0 || y < 0 || y > data->height)
		return (1);
	if (x < data->width && x >= 0 && y >= 0 && y < data->height \
		&& data->map[y][x] == '1')
		return (1);
	else
		return (0);
}
