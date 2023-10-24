/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:35 by asabri            #+#    #+#             */
/*   Updated: 2023/10/24 13:13:38 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42.h>
#include <math.h>
# include "../gc/ft_malloc.h"
  
#define FOV (60 * PI / 180)
#define wallAngle 90
#define Tile_size 64
#define MINI_MAP_SCALE 1.0
#define PI 3.14159265 
#define TOW_PI 6.28318530




typedef struct s_ray
{
	double	ray_angal;
	double	ax; 	
	double	ay;
	double	dx;
	double	dy;
	double	distance;
	bool	was_hit;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}t_ray; 
typedef struct s_player
{
	double	px;
	double	py;
	double	width;
	double	height;
	int		walkDirection;
	int		turnDirection; // 	-1 for left and +1 to right 
	double	rotationAngle;
	double	walkspeed;
	double	turnspeed;
	double	side_direction;
	
}t_player;
typedef struct	s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image_win;
	int				width;
	int				height;
	t_player		*player;
	char			**map;
}				t_data;
void	dda(t_data *data,double xstart, double ystart,double xend, double yend,int color);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
#endif