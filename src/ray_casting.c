/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:47:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/15 09:27:55 by asabri           ###   ########.fr       */
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

void norm_angle(double *angle, t_ray *ray)
{
	*angle = remainder(*angle, 2.0 * M_PI);
	if (*angle < 0)
		*angle = (2.0 * M_PI) + *angle;
	if (*angle > 0 && *angle < M_PI)
		ray->ray_face_up = 0;
	else
		ray->ray_face_up= 1;
	if (*angle < (0.5 * M_PI) || *angle > (1.5 * M_PI))
		ray->ray_face_right = 1;
	else
		ray->ray_face_right = 0;
}

void ray_hit_deriction(t_ray *ray)
{
	if (ray->horzhit)
	{
		if (ray->ray_face_up)
			ray->wall_deriction = NORTH;
		else
			ray->wall_deriction = SOUTH;
		return ;
	}
	if (ray->ray_face_right)
		ray->wall_deriction = EAST;
	else
		ray->wall_deriction = WEST;
}
unsigned int    *set_texture_colors(mlx_texture_t *png_strct)
{
    unsigned int    i;
    unsigned int    j;
	unsigned int *texture;

    i = 0;
    j = 0;
	texture = malloc(sizeof(unsigned int *) * (64 * 64));
    while (png_strct->pixels[i] && (j < png_strct->width * png_strct->height))
    {
        texture[j] = ft_pixel(png_strct->pixels[i],
                png_strct->pixels[i + 1],
                png_strct->pixels[i + 2],
                255);
        j++;
        i += png_strct->bytes_per_pixel;
    }
	return (texture);
}

uint32_t get_color(t_ray *ray,mlx_texture_t *texture,unsigned int yoffset,unsigned int xoffset)
{
	uint8_t *pixel;
	int pxl_loction;
	double height_divd;
	int height;
	
	if (ray->project_plan > HEIGHT)
		yoffset += (ray->project_plan - HEIGHT) / 2;
	height_divd = texture->height / ray->project_plan;
	height = floor((height_divd * yoffset)) * texture->width;
	pxl_loction = height;
	pxl_loction += xoffset;
	pxl_loction *= texture->bytes_per_pixel;
	pixel =&texture->pixels[pxl_loction];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
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
	unsigned int *texture;
	uint32_t color;

	color = 0;
	ray_inc = FOV / WIDTH;
	ray_start = data->player->rotationAngle - (FOV / 2.0);
	ray = malloc(sizeof(t_ray));
	colum = 0;
	texture = malloc(sizeof(unsigned int *)*(64 * 64));
	data->no = img_to_double_pointer(data->north);
	while (colum < WIDTH)
	{
		
		ray->horzhit = 0;
		ray->verthit = 0;
		ray->distanceh = INT_MAX;
		ray->distancev = INT_MAX;
		norm_angle(&ray_start, ray);
		horizontal(data,ray,ray_start);
		vertical(data,ray,ray_start);
		if(ray->horzhit)
			ray->distanceh = sqrt(pow((ray->hax - data->player->px), 2) + pow((ray->hay - data->player->py), 2));
		if(ray->verthit)
			ray->distancev = sqrt(pow((ray->vax -data->player->px), 2) + pow((ray->vay - data->player->py), 2));
		if ((ray->distanceh < ray->distancev ) && ray->horzhit)
		{
			player_ray_dist = ray->distanceh * cos(data->player->rotationAngle - ray_start);
			xoffset = (fmod(ray->hax ,Tile_size) * data->north->width) / Tile_size;
			// xoffset *= data->north->width;
		}
		else
		{
			//offsetx
			player_ray_dist = ray->distancev * cos(data->player->rotationAngle - ray_start);
			xoffset = (fmod(ray->vay ,Tile_size) * data->north->width) / Tile_size;
			// xoffset *= data->north->width;
		}
		project_dist = (WIDTH / 2)/tan(FOV / 2);
		ray->project_plan = (project_dist / player_ray_dist) * Tile_size;
		ystart = (HEIGHT / 2) - (ray->project_plan / 2);
		yend = (HEIGHT / 2) + (ray->project_plan / 2);
		if (ystart < 0)
			ystart = 0;
		// if (ray->project_plan > HEIGHT)
		// {
		// 	ystart = 0;
		// 	yend = HEIGHT;
		// }
		// yoffset = 0;
		// printf("%f\n", yend);
		// exit(0);
		while (ystart < yend && ystart < HEIGHT)
		{
			
			// color = get_color(ray,data->north,yoffset,xoffset);
			// yoffset = (ystart - (HEIGHT / 2)) - (ray->project_plan / 2.0) * data->north->height/ ray->project_plan;
			yoffset = ((ystart - ((HEIGHT / 2.0) - (ray->project_plan / 2.0))) \
						* data->north->height) / ray->project_plan;
			// texture = set_texture_colors(data->north);
			// printf("%f\n", ystart);
			// exit(0);
			mlx_put_pixel(data->image_win ,colum ,ystart, data->no[(int)yoffset][(int)xoffset]);
			ystart++;
		}
		















		// double d;
		// while (ystart < yend && ystart < HEIGHT)
		// {
		// 	// d = ystart + ((project_plan - HEIGHT) / 2);
		// 	// yoffset = (d * Tile_size) / project_plan;
		// 	// unsigned int color;
		// 	// set_texture_colors(data->north,texture);
		// 	// color = texture[yoffset * Tile_size + xoffset];
		// 	// int color = arr[offsety * ht + offsetx];
		// 	mlx_put_pixel(data->image_win,colum,ystart,color);
		// 	ystart++;
		// 	//i++;
		// }
		ray_start += ray_inc;
		colum++;
	}
}