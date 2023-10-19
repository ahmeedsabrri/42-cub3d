/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/19 16:23:11 by asabri           ###   ########.fr       */
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
			mlx_put_pixel(data->image_win, xstart, ystart,255);
			xstart = xstart + xinc;
			ystart = ystart + yinc;
	}
}


