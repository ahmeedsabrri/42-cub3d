/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:35 by asabri            #+#    #+#             */
/*   Updated: 2023/11/12 05:37:20 by asabri           ###   ########.fr       */
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
#include "../../MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <limits.h>
# include "../gc/ft_malloc.h"
  
#define PI 3.14159265 
#define FOV (60 * (M_PI / 180))
#define wallAngle 90
#define HEIGHT 720
#define WIDTH 1027
#define Tile_size 64
#define MINI_MAP_SCALE 0.2
#define TOW_PI 6.28318530
#define BUFFER_SIZE 1





typedef struct s_ray
{
	double	ray_angal;
	double	vax; 	
	double	vay;
	double	hax;
	double	hay;
	bool	horzhit;
	bool	verthit;
	double	distancev;
	double	distanceh;
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
	mlx_image_t		*minimap_win;
	int				width;
	int				height;
	t_player		*player;
	char			**map;
}	t_data;

void	init(t_data *data);
void	dda(t_data *data,double xstart, double ystart,double xend, double yend,int color);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	castallrays(t_data *data);
int		get_height(char **str);
int		width_size(char **str);
int	wall_hit(double posx, double posy, char **map);
//-------------parsing------------//


typedef struct s_infos
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
}	t_infos;

typedef struct s_text
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*fl;
	char	*ce;
}	t_text;

typedef struct s_floor
{
	int	r;
	int	g;
	int	b;
}	t_floor;

typedef struct s_ceiling
{
	int	r;
	int	g;
	int	b;
}	t_ceiling;


char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_error(char *str);
void	check_extension(char **av);
char	*strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strndup(char *str, size_t n);
char	*ft_strdup_n(const char *s1);
int		is_space(char c);
int     ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
int		check_infos(t_infos **infos);
int     ft_atoi(const char *str);
int		parsing(int ac, char **av, t_data *data);

//************linked_list***************//

// t_map	*ft_new_lst(char *line, t_type type);
// void	ft_add_data(t_map **head, char *line, t_type type);
// void	ft_delone(t_map *lst);
// void	ft_clear_lst(t_map **lst);

#endif
