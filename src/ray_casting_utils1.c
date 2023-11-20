/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:28:21 by asabri            #+#    #+#             */
/*   Updated: 2023/11/20 10:40:50 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	norm_angle(double *ray_start)
{
	*ray_start = remainder(*ray_start, 2.0 * M_PI);
	if (*ray_start < 0)
		*ray_start = (2.0 * M_PI) + *ray_start;
}

void	ray_hit_deriction(t_data *data, t_ray *ray, double angle)
{
	if (angle_up_or_down(angle))
	{
		ray->wall_deriction = SOUTH;
		ray->xoffset = (fmod(ray->hax, TILE_SIZE) * data->south->width) \
			/ TILE_SIZE;
	}
	else
	{
		ray->wall_deriction = NORTH;
		ray->xoffset = (fmod(ray->hax, TILE_SIZE) * data->north->width) \
			/ TILE_SIZE;
	}
}

void	ray_hit_deriction1(t_data *data, t_ray *ray, double angle)
{
	if (angle_left_or_right(angle))
	{
		ray->wall_deriction = WEST;
		ray->xoffset = (fmod(ray->vay, TILE_SIZE) * data->west->width) \
			/ TILE_SIZE;
	}
	else
	{
		ray->wall_deriction = EAST;
		ray->xoffset = (fmod(ray->vay, TILE_SIZE) * data->east->width) \
			/ TILE_SIZE;
	}
}

void	set_color(t_colors *colors, mlx_texture_t *img, unsigned int **pixels)
{
	colors->r = img->pixels[colors->count];
	colors->g = img->pixels[colors->count + 1];
	colors->b = img->pixels[colors->count + 2];
	colors->a = img->pixels[colors->count + 3];
	pixels[colors->i][colors->j] = \
	ft_pixel(colors->r, colors->g, colors->b, colors->a);
}

unsigned int	**png_to_dpointer(mlx_texture_t *img)
{
	unsigned int	**pixels;
	t_colors		colors;

	colors.i = 0;
	colors.count = 0;
	pixels = ft_malloc(sizeof(unsigned int *) * img->height, 1);
	if (!pixels)
		return (NULL);
	while (colors.i < img->height)
	{
		colors.j = 0;
		pixels[colors.i] = ft_malloc(sizeof(unsigned int) * img->width, 1);
		if (!pixels[colors.i])
			return (NULL);
		while (colors.j < img->width)
		{
			set_color(&colors, img, pixels);
			colors.j++;
			colors.count += 4;
		}
		colors.i++;
	}
	return (pixels);
}
