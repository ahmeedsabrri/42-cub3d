/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/24 13:29:39 by asabri           ###   ########.fr       */
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

void	dda(t_data *data,double xstart, double ystart,double xend, double yend,int color)
{
	double	dx;
	double	dy;
	double	xinc;
	double	yinc;
	int		step;

	dx = xstart - xend;
	dy = ystart - yend;
	step = ft_fabs(dx, dy);
	xinc = dx / step;
	yinc = dy / step;
	while (step--)
	{
        if (data->player->px < 12 * Tile_size && data->player->px>=0 && data->player->py >= 0 && data->player->py < data->height * Tile_size)
			mlx_put_pixel(data->image_win, xstart, ystart,color);
		xstart = xstart + xinc;
		ystart = ystart + yinc;
	}
}
int angle_left_or_right(double angle) 
{
    // Convert the angle to radians
    double radians = angle * M_PI / 180.0;

    // Use the sine function to determine the direction
    double cosvalue = cos(radians);
    if (cosvalue > 0) 
        return 1;  // Angle is facing right
    return 0; // Angle is facing left
}

int angle_up_or_down(double angle) 
{
    // Convert the angle to radians
    double radians = angle * M_PI / 180.0;

    // Use the sine function to determine the direction
    double sinValue = sin(radians);
    if (sinValue > 0) 
        return 1;  // Angle is facing up 
    return 0; // Angle is facing down
}

void vertical(t_data *data, t_ray *ray)
{
	double ax;
	double ay;
	double dx;
	double dy;
	
	ax = floor(data->player->px / Tile_size) * Tile_size;
	if (angle_left_or_right(data->player->rotationAngle))
		ax += Tile_size;
	ay = data->player->px + ((data->player->px - ax) * tan(data->player->rotationAngle));
	dx = Tile_size;
	dy = Tile_size * tan(data->player->rotationAngle);
}
void horizontal(t_data *data, t_ray *ray)
{
	double ax;
	double ay;
	double dx;
	double dy;
	
	ay = floor(data->player->py / Tile_size) * Tile_size;
	if (!angle_up_or_down(data->player->rotationAngle))
		ay += Tile_size;
	ax = data->player->px + ((data->player->py - ay) / tan(data->player->rotationAngle));
	dx = Tile_size;
	dy = Tile_size / tan(data->player->rotationAngle);
}
// void castallrays()
// {
// 	int colum;

// 	colum = 0;
// 	while (colum < 720)
// 	{
		
// 	}
// }