/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:35 by asabri            #+#    #+#             */
/*   Updated: 2023/10/19 15:31:56 by asabri           ###   ########.fr       */
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
	float	ray_angal; 	
	float	wall_hit_x; 	
	float	wall_hit_y;
	float	distance;
	bool	was_hit;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}t_ray; 
typedef struct s_player
{
	float	px;
	float	py;
	float	width;
	float	height;
	int		walkDirection;
	int		turnDirection; // 	-1 for left and +1 to right 
	float	rotationAngle;
	float	walkspeed;
	float	turnspeed;
	float	side_direction;
	
}t_player;
typedef struct	s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image_win;
	int				width;
	int				height;
	
	char			**map;
	t_player		*player;
}				t_data;

#endif