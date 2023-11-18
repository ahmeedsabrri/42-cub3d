/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/18 16:22:19 by asabri           ###   ########.fr       */
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

// void	dda(t_data *data,double xstart, double ystart,double xend, double yend,int color)
// {
// 	double	dx;
// 	double	dy;
// 	double	xinc;
// 	double	yinc;
// 	int		step;

// 	dx = xstart - xend;
// 	dy = ystart - yend;
// 	step = ft_fabs(dx, dy);
// 	xinc = dx / step;
// 	yinc = dy / step;
// 	while (step--)
// 	{
// 		if(xstart >=0 && xstart < WIDTH && ystart >=0 && ystart < HEIGHT)
// 			mlx_put_pixel(data->image_win, xstart, ystart,color);
// 		xstart = xstart + xinc;
// 		ystart = ystart + yinc;
// 	}
// }

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

int	wall_hit(double px, double py, t_data *data)
{
	int	x;
	int	y;

	x = (px / Tile_size);
	y = (py / Tile_size);
	if (x > (data->width) || x < 0 || y < 0 || y > (data->height))
		return (0);
	if (x < data->width && x >= 0
		&& y >= 0 && y < data->height && data->map[y][x] == '1')
		return (1);
	else
		return (0);
}


void castrayhorz(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy, double angle)
{
	double y;
	while (ax >= 0 && ay >= 0 && ax <= ((data->width) * Tile_size) && ay <= (data->height) * Tile_size)
	{
		if (!angle_up_or_down(angle))
			y = ay - 1;
		else
			y = ay;
		if (wall_hit(ax,y,data))
		{
			ray->hax = ax;
			ray->hay = ay;
			ray->horzhit = 1;
			break ;
		}
		else 
		{
			ax += dx;
			ay += dy;
		}
	}
}

void horizontal(t_data *data, t_ray *ray, double angle)
{
	double ax;
	double ay;
	double dx;
	double dy;
	
	dy = Tile_size;
	dx = Tile_size / tan(angle);
	if(!angle_up_or_down(angle))
		dy *=-1;
	ay = floor(data->player->py / Tile_size) * Tile_size;
	if (angle_up_or_down(angle) > 0)
		ay += Tile_size;
	ax = data->player->px + ((ay - data->player->py) / tan(angle));
	if ((!angle_left_or_right(angle) && dx > 0) || (angle_left_or_right(angle) && dx < 0))
		dx *= -1.0;
	castrayhorz(data,ray,ax,ay,dx,dy,angle);
}
void castrayvert(t_data *data, t_ray *ray,double ax, double ay,double dx,double dy,double angle)
{
	double x;
	while (ax >= 0 && ay >= 0 && ax <= ((data->width) * Tile_size) && ay <= (data->height) * Tile_size)
	{
		if (!angle_left_or_right(angle))
			x = ax - 1;
		else 
			x = ax;
		if (wall_hit(x,ay,data))
		{
			ray->vax = ax;
			ray->vay = ay;
			ray->verthit = 1;
			break ;
		}
		else 
		{
			ax += dx;
			ay += dy;
		}
	}
}
void vertical(t_data *data, t_ray *ray, double angle)
{
	double ax;
	double ay;
	double dx;
	double dy;
	
	ax = floor(data->player->px / Tile_size) * Tile_size;
	dx = Tile_size;
	if (angle_left_or_right(angle))
		ax += Tile_size;
	ay = data->player->py + ((ax - data->player->px) * tan(angle));
	if (!angle_left_or_right(angle))
		dx *= -1;
	dy = Tile_size * tan(angle);
	if ((!angle_up_or_down(angle) && dy > 0) || (angle_up_or_down(angle) && dy < 0))
		dy *= -1;
	castrayvert(data,ray,ax,ay,dx,dy,angle);
}

void norm_angle(double *angle)
{
	*angle = remainder(*angle, 2.0 * M_PI);
	if (*angle < 0)
		*angle = (2.0 * M_PI) + *angle;
}

void ray_hit_deriction(t_data *data,t_ray *ray, double *xoffset, double angle)
{
	if (angle_up_or_down(angle))
	{
		ray->wall_deriction = SOUTH;
		*xoffset = (fmod(ray->hax ,Tile_size) * data->south->width) / Tile_size;
	}
	else
	{
			ray->wall_deriction = NORTH;
			*xoffset = (fmod(ray->hax ,Tile_size) * data->north->width) / Tile_size;
	}
}
void ray_hit_deriction1(t_data *data,t_ray *ray, double *xoffset, double angle)
{
	
	if (angle_left_or_right(angle))
	{	
		ray->wall_deriction = EAST;
		*xoffset = (fmod(ray->vay ,Tile_size) * data->east->width) / Tile_size;
	}
	else
	{
		ray->wall_deriction = WEST;
		*xoffset = (fmod(ray->vay ,Tile_size) * data->west->width) / Tile_size;
	}
}

void	set_color(t_colors *colors, mlx_texture_t *img, uint32_t	**pixels)
{
	colors->r = img->pixels[colors->count];
	colors->g = img->pixels[colors->count + 1];
	colors->b = img->pixels[colors->count + 2];
	colors->a = img->pixels[colors->count + 3];
	pixels[colors->i][colors->j] = ft_pixel(colors->r,
			colors->g, colors->b, colors->a);
}
u_int32_t	**img_to_double_pointer(mlx_texture_t *img)
{
	uint32_t	**pixels;
	t_colors	colors;

	colors.i = 0;
	colors.count = 0;
	pixels = malloc(sizeof(uint32_t *) * img->height);
	if (!pixels)
		return (NULL);
	while (colors.i < img->height)
	{
		colors.j = 0;
		pixels[colors.i] = malloc(sizeof(uint32_t) * img->width);
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

void castallrays(t_data *data)
{
	int colum;
	t_ray *ray;
	double project_dist;
	double ystart;
	double yend;
	double ray_start;
	double player_ray_dist;
	double ray_inc;
	double xoffset;
	double yoffset;

	ray_inc = FOV / WIDTH;
	ray_start = data->player->rotationAngle - (FOV / 2.0);
	colum = 0;
	
	while (colum < WIDTH)
	{
		
		ray = malloc(sizeof(t_ray));
		memset(ray, 0, sizeof(t_ray));//ft_
		
		ray->horzhit = 0;
		ray->verthit = 0;
		ray->distanceh = ULONG_MAX;
		ray->distancev = ULONG_MAX;
		norm_angle(&ray_start);
		horizontal(data,ray,ray_start);
		vertical(data,ray,ray_start);
		ray->distanceh = sqrt(pow((ray->hax - data->player->px),2) + pow((ray->hay - data->player->py), 2));
		ray->distancev = sqrt(pow((ray->vax -data->player->px),2) + pow((ray->vay - data->player->py), 2));
		if((ray->distanceh < ray->distancev))
			ray_hit_deriction(data,ray, &xoffset,ray_start);
		else
			ray_hit_deriction1(data,ray, &xoffset,ray_start);
		if ((ray->distanceh < ray->distancev ) && ray->horzhit)
			player_ray_dist = ray->distanceh * cos(data->player->rotationAngle - ray_start);
		else
			player_ray_dist = ray->distancev * cos(data->player->rotationAngle - ray_start);
		project_dist = (WIDTH / 2)/tan(FOV / 2);
		ray->project_plan = (project_dist / player_ray_dist) * Tile_size;
		ystart = (HEIGHT / 2) - (ray->project_plan / 2);
		yend = (HEIGHT / 2) + (ray->project_plan / 2);
		if (ystart < 0)
			ystart = 0;
		while (ystart < yend && ystart < HEIGHT)
		{
			// if (ray->wall_deriction == NORTH)
			// {
			// 	yoffset = ((ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
			// 			* data->north->height) / ray->project_plan;
			// 	mlx_put_pixel(data->image_win ,colum ,ystart, data->no[(int)yoffset][(int)xoffset]);
			// 	// mlx_put_pixel(data->image_win ,colum ,ystart, ft_pixel(255,0,0,255));
			// }
			// if (ray->wall_deriction == SOUTH)
			// {
			// 	yoffset = ((ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
			// 			* data->south->height) / ray->project_plan;
			// 	mlx_put_pixel(data->image_win ,colum ,ystart, data->so[(int)yoffset][(int)(data->south->width - 1) - ((int)xoffset)]);
			// 	// mlx_put_pixel(data->image_win ,colum ,ystart, ft_pixel(255,255,0,255));
			// }
			// if (ray->wall_deriction == WEST)
			// {
				yoffset = ((ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
						* data->west->height) / ray->project_plan;
				mlx_put_pixel(data->image_win ,colum ,ystart, data->we[(int)yoffset][(int)(data->west->width - 1) - ((int)xoffset)]);
				// mlx_put_pixel(data->image_win ,colum ,ystart, ft_pixel(0,0,255,255));
			// }
			// if (ray->wall_deriction == EAST)
			// {
				// yoffset = ((ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
						// * data->east->height) / ray->project_plan;
				// mlx_put_pixel(data->image_win ,colum ,ystart, data->ea[(int)yoffset][(int)xoffset]);
				// mlx_put_pixel(data->image_win ,colum ,ystart, ft_pixel(0,255,255,255));
			// }
			
			ystart++;
			
		}
		ray_start += ray_inc;
		colum++;
		free(ray);
	}
}