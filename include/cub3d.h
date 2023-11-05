/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:35 by asabri            #+#    #+#             */
/*   Updated: 2023/10/24 01:45:55 by abberkac         ###   ########.fr       */
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
	double	wall_hit_x; 	
	double	wall_hit_y;
	double	distance;
	bool	was_hit;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_ray; 
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
	
}	t_player;

typedef struct	s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image_win;
	int				width;
	int				height;
	t_player		*player;
	char			**map;
}				t_data;


void	dda(t_data *data,double xstart, double ystart,double xend, double yend);
void	init(t_data *data);

//-------------parsing------------//

typedef enum s_type
{
	line,
	n_line
}	t_type;

typedef struct s_map
{
	char			*line;
	t_type			type;
	struct s_map	*next;
}	t_map;


char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_error(char *str);
void	check_extension(char **av);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *s, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strndup(char *str, size_t n);
int		parsing(int ac, char **av, t_data *data);

//************linked_list***************//

t_map	*ft_new_lst(char *line, t_type type);
void	ft_add_data(t_map **head, char *line, t_type type);
void	ft_delone(t_map *lst);
void	ft_clear_lst(t_map **lst);

#endif
