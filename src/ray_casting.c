/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/06 17:10:43 by abberkac         ###   ########.fr       */
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

void castrayhorz(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy, double angle)
{
	double y;
	while (ax >= 0 && ay >= 0 && ax <= 768 && ay <= 448)
	{
		if (!angle_up_or_down(angle))
			y = ay - 1;
		else
			y = ay;
		if (data->map[(int)(y / 64.0)][(int)(ax / 64.0)] == '1')
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
		dy*=-1;
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
	while (ax >= 0 && ay >= 0 && ax <= 768 && ay <= 448)
	{
		if (!angle_left_or_right(angle))
			x = ax - 1;
		else 
			x = ax;
		if (data->map[(int)(ay / 64.0)][(int)(x / 64.0)] == '1')
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
	double project_plan;
	double project_dist;
	double ystart;
	double yend;
	double ray_start;
	double player_ray_dist;
	double ray_inc;

	ray_inc = FOV / 1027;
	ray_start = data->player->rotationAngle - (FOV / 2.0);
	ray = malloc(sizeof(t_ray));
	colum = 0;
	
	while (colum < 1027)
	{
		
		ray->horzhit = 0;
		ray->verthit = 0;
		ray->distanceh = INT_MAX;
		ray->distancev = INT_MAX;
		norm_angle(&ray_start);
		horizontal(data,ray,ray_start);
		vertical(data,ray,ray_start);
		if(ray->horzhit)
			ray->distanceh = sqrt(pow((ray->hax - data->player->px),2) + pow((ray->hay - data->player->py),2));
		if(ray->verthit)
			ray->distancev = sqrt(pow((ray->vax -data->player->px),2) + pow((ray->vay - data->player->py),2));
		if ((ray->distanceh < ray->distancev ) && ray->horzhit)
		{
			player_ray_dist = ray->distanceh * cos(data->player->rotationAngle - ray_start);
			// dda(data,data->player->px,data->player->py,ray->hax,ray->hay,ft_pixel(0,255,0,255));
		}
		else
		{
			player_ray_dist = ray->distancev * cos(data->player->rotationAngle - ray_start);
			// dda(data,data->player->px,data->player->py,ray->vax,ray->vay,ft_pixel(255,0,0,255));
		}
		project_dist = (1027 / 2)/tan(FOV / 2);
		project_plan = (project_dist / player_ray_dist) * Tile_size;
		ystart = (720 / 2) - (project_plan / 2);
		yend = (720 / 2) + (project_plan / 2);
		// if (ystart > 720)
		// 	ystart = 0;
		if (ystart < 0)
			ystart = 0;
		// dda(data, colum, ystart, colum, yend, ft_pixel(0xfffffff,0xfffffff,0xfffffff,255));
		while (ystart < yend && ystart < 720.0)
		{
			mlx_put_pixel(data->image_win,colum,ystart,ft_pixel(255,255,255,255));
			ystart++;
		}
		ray_start += ray_inc;
		colum++;
	}
}