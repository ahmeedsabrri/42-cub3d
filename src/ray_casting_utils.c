/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:26:48 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 13:27:27 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double  ft_fabs(double dx, double dy)
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
        if ((x1) > WIDTH || (x1) < 0 || (y1) < 0 || (y1) > HEIGHT)
            return;
        mlx_put_pixel(data->image_win, round(x1), round(y1), color);
        x1 += xIncrement;
        y1 += yIncrement;
        i++;
    }
}

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

int wall_hit(double px, double py, t_data *data)
{
    int x;
    int y;

    x = (px / Tile_size);
    y = (py / Tile_size);
    if (x > data->width || x < 0 || y < 0 || y > data->height)
        return (1);
    if (x < data->width && x >= 0
        && y >= 0 && y < data->height && data->map[y][x] == '1')
        return (1);
    else
        return (0);
}