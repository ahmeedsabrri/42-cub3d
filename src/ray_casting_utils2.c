/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:30:03 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 22:12:16 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calcu_yoffset(t_data *data, t_ray *ray)
{
	if (ray->wall_deriction == NORTH)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan \
		/ 2.0))) * data->north->height) / ray->project_plan;
	if (ray->wall_deriction == SOUTH)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan \
		/ 2.0))) * data->south->height) / ray->project_plan;
	if (ray->wall_deriction == WEST)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan \
		/ 2.0))) * data->west->height) / ray->project_plan;
	if (ray->wall_deriction == EAST)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan \
		/ 2.0))) * data->east->height) / ray->project_plan;
}

void	draw_wall(t_data *data, t_ray *ray, int colum)
{
	while (ray->ystart < ray->yend && ray->ystart < HEIGHT)
	{
		calcu_yoffset(data, ray);
		if (ray->wall_deriction == NORTH)
			mlx_put_pixel(data->image_win, colum, ray->ystart, \
			data->no[(int)ray->yoffset][(int)ray->xoffset]);
		if (ray->wall_deriction == SOUTH)
			mlx_put_pixel(data->image_win, colum, ray->ystart, \
			data->so[(int)ray->yoffset][(int)(data->south->width - 1) \
			- ((int)ray->xoffset)]);
		if (ray->wall_deriction == WEST)
			mlx_put_pixel(data->image_win, colum, ray->ystart, \
			data->we[(int)ray->yoffset][(int)(data->west->width - 1) \
			- ((int)ray->xoffset)]);
		if (ray->wall_deriction == EAST)
			mlx_put_pixel(data->image_win, colum, ray->ystart, \
			data->ea[(int)ray->yoffset][(int)ray->xoffset]);
		ray->ystart++;
	}
}

void	projection_calcul(t_ray *ray)
{
	ray->project_dist = (WIDTH / 2) / tan(FOV / 2);
	ray->project_plan = (ray->project_dist / ray->player_ray_dist) * TILE_SIZE;
	ray->ystart = (HEIGHT / 2) - (ray->project_plan / 2);
	ray->yend = (HEIGHT / 2) + (ray->project_plan / 2);
	if (ray->ystart < 0)
		ray->ystart = 0;
}

void	calculate_distence(t_ray *ray, t_data *data, double ray_start)
{
	if (ray->horzhit)
		ray->distanceh = sqrt(pow((ray->hax - data->player->px), 2) \
		+ pow((ray->hay - data->player->py), 2));
	if (ray->verthit)
		ray->distancev = sqrt(pow((ray->vax - data->player->px), 2) \
		+ pow((ray->vay - data->player->py), 2));
	if ((ray->distanceh < ray->distancev) && ray->horzhit)
	{
		ray->player_ray_dist = ray->distanceh * cos(data->player->rotat_angle \
		- ray_start);
		ray_hit_deriction(data, ray, ray_start);
		ray->horzhit = 1;
		ray->verthit = 0;
	}
	else
	{
		ray->player_ray_dist = ray->distancev * cos(data->player->rotat_angle \
			- ray_start);
		ray_hit_deriction1(data, ray, ray_start);
		ray->horzhit = 0;
		ray->verthit = 1;
	}
	projection_calcul(ray);
}
