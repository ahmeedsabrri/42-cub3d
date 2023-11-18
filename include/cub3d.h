/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:35 by asabri            #+#    #+#             */
/*   Updated: 2023/11/18 15:35:49 by abberkac         ###   ########.fr       */
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
#define WIDTH 1024
#define Tile_size 64
#define MINI_MAP_SCALE 0.2
#define TOW_PI 6.28318530
#define BUFFER_SIZE 1


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
	int i;
    int idx;
    int c;
    int count;
    char *tmp;
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
	int ray_face_up;
	int ray_face_right;
	t_dir wall_deriction;
	double project_plan;
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
	mlx_t		*mlx;
	mlx_image_t	*image_win;
	int			width;
	t_infos		*infos;
	t_floor		*floor;
	t_ceiling	*ceiling;
	char		plyr;
	int			height;
	t_player	*player;
	char		**map;
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *east;
	mlx_texture_t *west;
	uint32_t	**no;
	uint32_t	**so;
	uint32_t	**we;
	uint32_t	**ea;
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

void	init(t_data *data);
void	dda(t_data *data,double xstart, double ystart,double xend, double yend,int color);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	castallrays(t_data *data);
int		get_height(char **str);
int		width_size(char **str);
int		wall_hit(double px, double py, t_data *data);
u_int32_t	**img_to_double_pointer(mlx_texture_t *img);

//-------------parsing------------//




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
int		check_infos(t_infos **infos, t_data **data);
int     ft_atoi(const char *str);
int		check_map_valid(t_data **data);
int		resize_to_same_width(t_data **data);
int		store_map(int fd, t_data **data, int count, char *line);
int		store_valid_infos(char **str, int flag);
int		check_colors_valid(char *color);
int		fill_rgb_colors(t_floor **floor, t_ceiling **ceiling, char *fl, char *cl);
int		get_textures(t_infos **infos, char *line);
int		dup_check_infos(char **str, char *line);
void	init_infos(t_infos *infos);
void	init_vars(t_varaible *var, int flag);
int		check_zeros_and_player(char **map, char plyr, int *i);
int		condition(char c);
int		existence_condition(t_infos *infos);
int		parsing(char **av, t_data *data);

//************linked_list***************//

// t_map	*ft_new_lst(char *line, t_type type);
// void	ft_add_data(t_map **head, char *line, t_type type);
// void	ft_delone(t_map *lst);
// void	ft_clear_lst(t_map **lst);

#endif
