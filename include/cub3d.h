/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:35 by asabri            #+#    #+#             */
/*   Updated: 2023/11/20 12:16:02 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../gc/ft_malloc.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

# define PI 3.14159265 
# define FOV 1.0472
// # define wallAngle 90
# define HEIGHT 720
# define WIDTH 1024
# define TILE_SIZE 64
# define MINI_MAP_SCALE 0.2
# define TOW_PI 6.28318530
# define BUFFER_SIZE 1

typedef struct s_infos
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
}	t_infos;

typedef struct s_variable
{
	int		i;
	int		idx;
	int		c;
	int		count;
	char	*tmp;
}	t_varaible;

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

typedef enum s_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}t_dir;

typedef struct s_point
{
	double	px1;
	double	py1;
	double	px2;
	double	py2;
}t_point;
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
	int		ray_face_up;
	int		ray_face_right;
	t_dir	wall_deriction;
	double	project_plan;
	double	project_dist;
	double	ystart;
	double	yend;
	double	player_ray_dist;
	double	xoffset;
	double	yoffset;
}	t_ray; 

typedef struct s_player
{
	double	px;
	double	py;
	double	width;
	double	height;
	int		walk_direct;
	int		turn_direct; 
	double	rotat_angle;
	double	walkspeed;
	double	turnspeed;
	double	side_direction;
}	t_player;

typedef struct s_m_map
{
	double	xstart;
	double	ystart;
	double	distance;
	int		i;
	int		j;
}	t_m_map;

typedef struct s_dda
{
	int		i;
	double	steps;
	double	dx;
	double	dy;
	double	x_increment;
	double	y_increment;
}	t_dda;

typedef struct s_horiz
{
	double	ax;
	double	ay;
	double	dx;
	double	dy;
}	t_horz;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image_win;
	int				width;
	t_infos			*infos;
	t_floor			*floor;
	t_ceiling		*ceiling;
	char			plyr;
	int				height;
	t_player		*player;
	char			**map;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	uint32_t		**no;
	uint32_t		**so;
	uint32_t		**we;
	uint32_t		**ea;
}	t_data;

typedef struct s_colors
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	i;
	uint32_t	j;
	int			count;
}				t_colors;

//--------------- Ray Casting & Textures -----------------------//

void			dda(t_data *data, t_point point, int color);
void			set_color(t_colors *colors, mlx_texture_t *img, \
				unsigned int **pixels);
void			calculate_distence(t_ray *ray, t_data *data, double ray_start);
void			ray_hit_deriction1(t_data *data, t_ray *ray, double angle);
void			ft_keyfunc_pressed(mlx_key_data_t keypress, void *param);
void			ray_hit_deriction(t_data *data, t_ray *ray, double angle);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			vertical(t_data *data, t_ray *ray, double angle);
void			draw_wall(t_data *data, t_ray *ray, int colum);
int				wall_hit(double px, double py, t_data *data);
int				wall_hit(double px, double py, t_data *data);
void			calcu_yoffset(t_data *data, t_ray *ray);
unsigned int	**png_to_dpointer(mlx_texture_t *img);
int				angle_left_or_right(double angle);
void			ft_renderplayer1(t_data *data);
int				angle_up_or_down(double angle);
double			ft_fabs(double dx, double dy);
void			norm_angle(double *ray_start);
void			ft_renderplayer(t_data *data);
void			wall_projection(t_data *data);
void			get_player_pos(t_data *data);
void			renderminimap(t_data *data);
int				get_height(char **str);
int				width_size(char **str);
void			ft_hook(void *param);
void			init(t_data *data);

//----------------------------parsing-------------------------------//

int				fill_rgb_colors(t_floor **floor, t_ceiling **ceiling, \
				char *fl, char *cl);
int				store_map(int fd, t_data **data, int count, char *line);
int				check_zeros_and_player(char **map, char plyr, int *i);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				check_infos(t_infos **infos, t_data **data);
int				get_textures(t_infos **infos, char *line);
int				ft_strcmp(const char *s1, const char *s2);
int				dup_check_infos(char **str, char *line);
int				store_valid_infos(char **str, int flag);
void			init_vars(t_varaible *var, int flag);
int				existence_condition(t_infos *infos);
int				resize_to_same_width(t_data **data);
char			*ft_strrchr(const char *s, int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strndup(char *str, size_t n);
int				parsing(char **av, t_data *data);
int				check_colors_valid(char *color);
void			checking_condition(char line);
int				check_map_valid(t_data **data);
char			*strjoin(char *s1, char *s2);
char			*ft_strdup_n(const char *s1);
void			check_extension(char **av);
char			*ft_strdup(const char *s1);
void			init_infos(t_infos *infos);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
char			*get_next_line(int fd);
void			ft_error(char *str);
int				ft_isdigit(int c);
int				condition(char c);
int				is_space(char c);

#endif		
