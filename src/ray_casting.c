/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 13:31:37 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void castrayhorz(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy, double angle)
{
    double y;
    while (ax >= 0 && ay >= 0 && ax <= ((data->width) * Tile_size) && ay <= (data->height) * Tile_size)
    {
        if (!angle_up_or_down(angle))
            y = ay - 1;
        else
            y = ay;
        if (wall_hit(ax,y,data))
        {
            ray->hax = ax;
            ray->hay = ay;
            ray->horzhit = 1;
            break ;
        }
        else 
        {
            ax += dx;
            ay += dy;
        }
    }
}

void horizontal(t_data *data, t_ray *ray, double angle)
{
    double ax;
    double ay;
    double dx;
    double dy;
    
    dy = 64.0;
    dx = 64.0 / tan(angle);
    if(!angle_up_or_down(angle))
        dy *=-1;
    ay = floor(data->player->py / 64.0) * 64.0;
    if (angle_up_or_down(angle) > 0)
        ay += 64.0;
    ax = data->player->px + ((ay - data->player->py) / tan(angle));
    if ((!angle_left_or_right(angle) && dx > 0) || (angle_left_or_right(angle) && dx < 0))
        dx *= -1.0;
    castrayhorz(data,ray,ax,ay,dx,dy,angle);
}
void castrayvert(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy,double angle)
{
    double x;
    while (ax >= 0 && ay >= 0 && ax <= ((data->width) * Tile_size) && ay <= (data->height) * Tile_size)
    {
        if (!angle_left_or_right(angle))
            x = ax - 1;
        else 
            x = ax;
        if (wall_hit(x,ay,data))
        {
            ray->vax = ax;
            ray->vay = ay;
            ray->verthit = 1;
            break ;
        }
        else 
        {
            ax += dx;
            ay += dy;
        }
    }
}
void vertical(t_data *data, t_ray *ray, double angle)
{
    double ax;
    double ay;
    double dx;
    double dy;
    
    ax = floor(data->player->px / 64.0) * 64.0;
    dx = 64.0;
    if (angle_left_or_right(angle))
        ax += 64.0;
    ay = data->player->py + ((ax - data->player->px) * tan(angle));
    if (!angle_left_or_right(angle))
        dx *= -1;
    dy = Tile_size * tan(angle);
    if ((!angle_up_or_down(angle) && dy > 0) || (angle_up_or_down(angle) && dy < 0))
        dy *= -1;
    castrayvert(data,ray,ax,ay,dx,dy,angle);
}

void wall_projection(t_data *data)
{
    t_ray *ray;int colum;double ray_start;
    double ray_inc;	
	
	ray_inc = FOV / WIDTH;
	ray_start = data->player->rotationAngle - (FOV / 2.0);
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
        horizontal(data,ray,ray_start);
        vertical(data,ray,ray_start);
        calculate_distence(ray,data,ray_start);
        draw_wall(data,ray,colum);
        free(ray);
        ray_start += ray_inc;
        colum++;
    }
}

