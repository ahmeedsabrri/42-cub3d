/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/19 17:43:17 by asabri           ###   ########.fr       */
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

void	dda(t_data *data,double xstart, double ystart,double xend, double yend)
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
			mlx_put_pixel(data->image_win, xstart, ystart,255);
		xstart = xstart + xinc;
		ystart = ystart + yinc;
	}
}


