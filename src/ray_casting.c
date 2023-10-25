/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/25 18:40:46 by asabri           ###   ########.fr       */
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

void dda(t_data *data, double x1, double y1, double x2, double y2, int color)
{
    int i;
    double steps;
	double dx;
	double dy;
	double xIncrement, yIncrement;

    dx = x2 - x1;
    dy = y2 - y1;
    i = 0;
    steps = fmax(fabs(dx), fabs(dy));
    if (steps == 0)
    {
        mlx_put_pixel(data->image_win, round(x1), round(y1), color);
        return;
    }
    xIncrement = dx / steps;
    yIncrement = dy / steps;
    while (i <= steps)
    {
        if ((x1) > 1027 || (x1) < 0 || (y1) < 0 || (y1) > 720)
            return;
        mlx_put_pixel(data->image_win, round(x1), round(y1), color);
        x1 += xIncrement;
        y1 += yIncrement;
        i++;
    }
}

// void	dda(t_data *data,double xstart, double ystart,double xend, double yend,int color)
// {
// 	double	dx;
// 	double	dy;
// 	double	xinc;
// 	double	yinc;
// 	int		step;

// 	dx = xstart - xend;
// 	dy = ystart - yend;
// 	step = ft_fabs(dx, dy);
// 	xinc = dx / step;
// 	yinc = dy / step;
// 	while (step--)
// 	{
// 		if(xstart >=0 && xstart < 1027 && ystart >=0 && ystart < 720)
// 			mlx_put_pixel(data->image_win, xstart, ystart,color);
// 		xstart = xstart + xinc;
// 		ystart = ystart + yinc;
// 	}
// }
int angle_left_or_right(double angle) 
{
    if (angle < (M_PI / 2) || angle > ((3 *M_PI)/2))
		return 1;
    return 0; // Angle is facing left
}

int angle_up_or_down(double angle) 
{
	if (angle > 0 && angle < M_PI)
		return 1;
    return 0; // Angle is facing up
}
void castrayvert(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy,double angle)
{
	double x;
	while (ax >= 0 && ay >= 0 && ax <= 768 && ay <= 448)
	{
		if (!angle_left_or_right(angle))
			x = ax - 1;
		else 
			x = ax;
		if (data->map[(int)(ay / Tile_size)][(int)(x / Tile_size)] == '1')
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
void castrayhorz(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy, double angle)
{
	double y;
	while (ax >= 0 && ay >= 0 && ax <= 768 && ay <= 448)
	{
		if (!angle_up_or_down(angle))
			y = ay - 1;
		else
			y = ay;
		if (data->map[(int)(y / Tile_size)][(int)(ax / Tile_size)] == '1')
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
void vertical(t_data *data, t_ray *ray, double angle)
{
	double ax;
	double ay;
	double dx;
	double dy;
	
	ax = floor(data->player->px / Tile_size) * Tile_size;
	dx = Tile_size;
	if (angle_left_or_right(angle))
		ax += Tile_size;
	ay = data->player->py + ((data->player->px - ax) * tan(angle));
	if (!angle_left_or_right(angle))
		dx *= -1;
	dy = Tile_size * tan(angle);
	if ((!angle_up_or_down(angle) && dy > 0) || (angle_up_or_down(angle) && dy < 0))
		dy *= -1;
	castrayvert(data,ray,ax,ay,dx,dy,angle);
}
void horizontal(t_data *data, t_ray *ray, double angle)
{
	double ax;
	double ay;
	double dx;
	double dy;
	
	ay = floor(data->player->py / Tile_size) * Tile_size;
	if (angle_up_or_down(angle))
		ay += Tile_size;
	ax = data->player->px + ((data->player->py - ay) / tan(angle));
	dy = Tile_size;
	if(!angle_up_or_down(angle))
		dy*=-1;
	dx = Tile_size / tan(angle);
	if ((!angle_left_or_right(angle) && dx > 0) || (angle_left_or_right(angle) && dx < 0))
		dx *= -1;
	castrayhorz(data,ray,ax,ay,dx,dy,angle);
}
void norm_angle(double *angle)
{
	*angle = remainder(*angle, 2.0 * M_PI);
	if (*angle < 0)
		*angle = (2.0 * M_PI) + *angle;
}

void castallrays(t_data *data)
{
	int colum;
	t_ray *ray;
	double ray_start;
	double ray_inc;

	ray_inc = FOV / 768.0;
	ray_start = data->player->rotationAngle - (FOV / 2.0);
	ray = malloc(sizeof(t_ray));
	colum = 0;
	
	while (colum < 1)
	{
		
		ray->horzhit = 0;
		ray->verthit = 0;
		ray->distanceh = INT_MAX;
		ray->distancev = INT_MAX;
		norm_angle(&ray_start);
		horizontal(data,ray,ray_start);
		vertical(data,ray,ray_start);
		//if(ray->horzhit)
		//	ray->distanceh = sqrt(pow((ray->hax - data->player->px),2) + pow((ray->hay - data->player->py),2));
		// if(ray->verthit)
		//	ray->distancev = sqrt(pow((ray->vax -data->player->px),2) + pow((ray->vay - data->player->py),2));
		//if (ray->distanceh < ray->distancev)
		if(ray->horzhit)
			dda(data,data->player->px,data->player->py,ray->hax,ray->hay,ft_pixel(0,255,0,255));
		//else
		if(ray->verthit)
			dda(data,data->player->px,data->player->py,ray->vax,ray->vay,ft_pixel(0,255,0,255));
		ray_start +=ray_inc;
		// printf("ray_start:%lf col:%d\n",ray_start,colum);
		colum++;
	}
}