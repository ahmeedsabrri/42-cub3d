/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 18:09:51 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	castrayhorz(t_data *data, t_ray *ray, t_horz horz, double angle)
{
	double	y;

	while (horz.ax >= 0 && horz.ay >= 0 && horz.ax \
		<= ((data->width) * TILE_SIZE) \
		&& horz.ay <= (data->height) * TILE_SIZE)
	{
		if (!angle_up_or_down(angle))
			y = horz.ay - 1;
		else
			y = horz.ay;
		if (wall_hit(horz.ax, y, data))
		{
			ray->hax = horz.ax;
			ray->hay = horz.ay;
			ray->horzhit = 1;
			break ;
		}
		else
		{
			horz.ax += horz.dx;
			horz.ay += horz.dy;
		}
	}
}

void	horizontal(t_data *data, t_ray *ray, double angle)
{
	t_horz	horz;

	horz.dy = 64.0;
	horz.dx = 64.0 / tan(angle);
	if (!angle_up_or_down(angle))
		horz.dy *= -1;
	horz.ay = floor(data->player->py / 64.0) * 64.0;
	if (angle_up_or_down(angle) > 0)
		horz.ay += 64.0;
	horz.ax = data->player->px + ((horz.ay - data->player->py) / tan(angle));
	if ((!angle_left_or_right(angle) && horz.dx > 0) || \
		(angle_left_or_right(angle)
			&& horz.dx < 0))
		horz.dx *= -1.0;
	castrayhorz(data, ray, horz, angle);
}

void	castrayvert(t_data *data, t_ray *ray, t_horz vert, double angle)
{
	double	x;

	while (vert.ax >= 0 && vert.ay >= 0 && vert.ax \
		<= ((data->width) * TILE_SIZE) \
		&& vert.ay <= (data->height) * TILE_SIZE)
	{
		if (!angle_left_or_right(angle))
			x = vert.ax - 1;
		else
			x = vert.ax;
		if (wall_hit(x, vert.ay, data))
		{
			ray->vax = vert.ax;
			ray->vay = vert.ay;
			ray->verthit = 1;
			break ;
		}
		else
		{
			vert.ax += vert.dx;
			vert.ay += vert.dy;
		}
	}
}

void	vertical(t_data *data, t_ray *ray, double angle)
{
	t_horz	vert;

	vert.ax = floor(data->player->px / 64.0) * 64.0;
	vert.dx = 64.0;
	if (angle_left_or_right(angle))
		vert.ax += 64.0;
	vert.ay = data->player->py + ((vert.ax - data->player->px) * tan(angle));
	if (!angle_left_or_right(angle))
		vert.dx *= -1;
	vert.dy = TILE_SIZE * tan(angle);
	if ((!angle_up_or_down(angle) && vert.dy > 0) || (angle_up_or_down(angle) \
		&& vert.dy < 0))
		vert.dy *= -1;
	castrayvert(data, ray, vert, angle);
}

void	wall_projection(t_data *data)
{
	t_ray	*ray;
	int		colum;
	double	ray_start;
	double	ray_inc;

	ray_inc = FOV / WIDTH;
	ray_start = data->player->rotat_angle - (FOV / 2.0);
	colum = 0;
	while (colum < WIDTH)
	{
		ray = malloc(sizeof(t_ray));
		memset(ray, 0, sizeof(t_ray));
		ray->horzhit = 0;
		ray->verthit = 0;
		ray->distanceh = INT_MAX;
		ray->distancev = INT_MAX;
		norm_angle(&ray_start);
		horizontal(data, ray, ray_start);
		vertical(data, ray, ray_start);
		calculate_distence(ray, data, ray_start);
		draw_wall(data, ray, colum);
		free(ray);
		ray_start += ray_inc;
		colum++;
	}
}
