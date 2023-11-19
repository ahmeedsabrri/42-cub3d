/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/19 12:49:08 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double  ft_fabs(double dx, double dy)
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

int wall_hit(double px, double py, t_data *data)
{
    int x;
    int y;

    x = (px / Tile_size);
    y = (py / Tile_size);
    if (x > data->width || x < 0 || y < 0 || y > data->height)
        return (1);
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
    
    dy = 64.0;
    dx = 64.0 / tan(angle);
    if(!angle_up_or_down(angle))
        dy *=-1;
    ay = floor(data->player->py / 64.0) * 64.0;
    if (angle_up_or_down(angle) > 0)
        ay += 64.0;
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
    
    ax = floor(data->player->px / 64.0) * 64.0;
    dx = 64.0;
    if (angle_left_or_right(angle))
        ax += 64.0;
    ay = data->player->py + ((ax - data->player->px) * tan(angle));
    if (!angle_left_or_right(angle))
        dx *= -1;
    dy = Tile_size * tan(angle);
    if ((!angle_up_or_down(angle) && dy > 0) || (angle_up_or_down(angle) && dy < 0))
        dy *= -1;
    castrayvert(data,ray,ax,ay,dx,dy,angle);
}


void norm_angle(double *ray_start)
{
    *ray_start = remainder(*ray_start, 2.0 * M_PI);
    if (*ray_start < 0)
        *ray_start = (2.0 * M_PI) + *ray_start;
}

void ray_hit_deriction(t_data *data,t_ray *ray,double angle)
{
	if (angle_up_or_down(angle))
	{
		ray->wall_deriction = SOUTH;
		ray->xoffset = (fmod(ray->hax ,Tile_size) * data->south->width) / Tile_size;
	}
	else
	{
			ray->wall_deriction = NORTH;
			ray->xoffset = (fmod(ray->hax ,Tile_size) * data->north->width) / Tile_size;
	}
}
void ray_hit_deriction1(t_data *data,t_ray *ray,double angle)
{
	
	if (angle_left_or_right(angle))
	{
		ray->wall_deriction = WEST;
		ray->xoffset = (fmod(ray->vay ,Tile_size) * data->west->width) / Tile_size;
	}
	else
	{
		ray->wall_deriction = EAST;
		ray->xoffset = (fmod(ray->vay ,Tile_size) * data->east->width) / Tile_size;
	}
}

void    set_color(t_colors *colors, mlx_texture_t *img, uint32_t    **pixels)
{
    colors->r = img->pixels[colors->count];
    colors->g = img->pixels[colors->count + 1];
    colors->b = img->pixels[colors->count + 2];
    colors->a = img->pixels[colors->count + 3];
    pixels[colors->i][colors->j] = ft_pixel(colors->r,
            colors->g, colors->b, colors->a);
}
u_int32_t   **img_to_double_pointer(mlx_texture_t *img)
{
    uint32_t    **pixels;
    t_colors    colors;

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
void calcu_yoffset(t_data *data,t_ray *ray)
{
	if (ray->wall_deriction == NORTH)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
				* data->north->height) / ray->project_plan;
	if (ray->wall_deriction == SOUTH)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
				* data->south->height) / ray->project_plan;
	if (ray->wall_deriction == WEST)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
				* data->west->height) / ray->project_plan;
	if (ray->wall_deriction == EAST)
		ray->yoffset = ((ray->ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
			* data->east->height) / ray->project_plan;
}
void draw_wall(t_data *data,t_ray *ray, int colum)
{
	while (ray->ystart < ray->yend && ray->ystart < HEIGHT)
    {
		calcu_yoffset(data,ray);
		if (ray->wall_deriction == NORTH)
			mlx_put_pixel(data->image_win ,colum ,ray->ystart, data->no[(int)ray->yoffset][(int)ray->xoffset]);
		if (ray->wall_deriction == SOUTH)
			mlx_put_pixel(data->image_win ,colum ,ray->ystart, data->so[(int)ray->yoffset][(int)(data->south->width - 1) - ((int)ray->xoffset)]);
		if (ray->wall_deriction == WEST)
			mlx_put_pixel(data->image_win ,colum ,ray->ystart, data->we[(int)ray->yoffset][(int)(data->west->width - 1) - ((int)ray->xoffset)]);
		if (ray->wall_deriction == EAST)
			mlx_put_pixel(data->image_win ,colum ,ray->ystart, data->ea[(int)ray->yoffset][(int)ray->xoffset]);
        ray->ystart++;
    }
}

void calculate_distence(t_ray *ray, t_data *data, double ray_start)
{
	if(ray->horzhit)
        ray->distanceh = sqrt(pow((ray->hax - data->player->px), 2) + pow((ray->hay - data->player->py), 2));
    if(ray->verthit)
        ray->distancev = sqrt(pow((ray->vax -data->player->px), 2) + pow((ray->vay - data->player->py), 2));
    if ((ray->distanceh < ray->distancev ) && ray->horzhit)
    {
        ray->player_ray_dist = ray->distanceh * cos(data->player->rotationAngle - ray_start);
        ray_hit_deriction(data,ray,ray_start);
        ray->horzhit = 1;
        ray->verthit = 0;
    }
    else
    {
        ray->player_ray_dist = ray->distancev * cos(data->player->rotationAngle - ray_start);
        ray_hit_deriction1(data,ray,ray_start);
        ray->horzhit = 0;
        ray->verthit = 1;
    }
    ray->project_dist = (WIDTH / 2)/tan(FOV / 2);
    ray->project_plan = (ray->project_dist / ray->player_ray_dist) * Tile_size;
    ray->ystart = (HEIGHT / 2) - (ray->project_plan / 2);
    ray->yend = (HEIGHT / 2) + (ray->project_plan / 2);
	 if (ray->ystart < 0)
            ray->ystart = 0;
}
void wall_projection(t_data *data)
{
    t_ray *ray;int colum;double ray_start;
    double ray_inc;	
	
	ray_inc = FOV / WIDTH;
	ray_start = data->player->rotationAngle - (FOV / 2.0);
	colum = 0;
    while (colum < WIDTH)
    {
        ray = malloc(sizeof(t_ray));
        memset(ray, 0, sizeof(t_ray));
        ray->horzhit = 0;
        ray->verthit = 0;
        ray->distanceh = INT_MAX;
        ray->distancev = INT_MAX;
        norm_angle(&ray_start);
        horizontal(data,ray,ray_start);
        vertical(data,ray,ray_start);
        calculate_distence(ray,data,ray_start);
        draw_wall(data,ray,colum);
        free(ray);
        ray_start += ray_inc;
        colum++;
    }
}

