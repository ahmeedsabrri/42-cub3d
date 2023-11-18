/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/18 16:40:37 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


// void dda(t_data *data, double x1, double y1, double x2, double y2, int color)
// {
//     int i;
//     double steps;
// 	double dx;
// 	double dy;
// 	double xIncrement, yIncrement;

//     dx = x2 - x1;
//     dy = y2 - y1;
//     i = 0;
//     steps = fmax(fabs(dx), fabs(dy));
//     if (steps == 0)
//     {
//         mlx_put_pixel(data->image_win, round(x1), round(y1), color);
//         return;
//     }
//     xIncrement = dx / steps;
//     yIncrement = dy / steps;
//     while (i <= steps)
//     {
//         if ((x1) > WIDTH || (x1) < 0 || (y1) < 0 || (y1) > HEIGHT)
//             return;
//         mlx_put_pixel(data->image_win, round(x1), round(y1), color);
//         x1 += xIncrement;
//         y1 += yIncrement;
//         i++;
//     }
// }
void init(t_data *data);
//(255,255,0)yellow color
// void draw_player(t_data *data, uint32_t color)
// {
//     (void)color;
//     for (int i = 0; i < 360; i++)
//         dda(data,data->player->px ,data->player->py ,data->player->px + (cos(i * PI/180) * 10),data->player->py + (sin(i * PI/180) * 10),ft_pixel(255,0,0,255));
//     dda(data,data->player->px,data->player->py,data->player->px + (cos(data->player->rotationAngle) * 30),data->player->py + (sin(data->player->rotationAngle) * 30),ft_pixel(255,0,0,255));
// }
// void draw_square(t_data *data, int y,int x, uint32_t color)
// {
//     (void)color;
//     for (int i = 0; i < Tile_size - 1; i++)
//         for (int j = 0; j < Tile_size - 1; j++)
//         {
//             mlx_put_pixel(data->image_win, (x + i) * MINI_MAP_SCALE, (y + j) * MINI_MAP_SCALE, ft_pixel(color,color,color,color));
//         }
// }
// void draw_map(t_data *data)
// {
//     int i;
//     int j;

//     i = -1;
//     data->width = 0;
//     data->height = 0;
//     while (data->map[++i])
//     {
//         j = -1;
//         while (data->map[i][++j])
//         {
//             if (data->map[i][j] == '1')
//                 draw_square(data,i * Tile_size, j * Tile_size , 0x5a5a5a);
//             else 
//                 draw_square(data,i * 64, j * 64, 0x808080);
//             data->width++;
//         }
//         data->height++;
//     }
// }
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void draw_player(t_data *data, uint32_t color)
{
    (void)color;
    for (int i = 0; i < 360; i++)
        dda(data,(200 / 2) ,(200 / 2),(200 / 2) + (cos(i * PI/180) * 10),(200 / 2) + (sin(i * PI/180) * 10),ft_pixel(1,85,172,200));
    dda(data,(200/ 2) ,(200 / 2) ,(200/ 2) + (cos(data->player->rotationAngle) * 30),(200 / 2) + (sin(data->player->rotationAngle) * 30),ft_pixel(1,85,172,200));
}
void draw_minimap(t_data *data, double xstart,double ystart,int i,int j,double distance)
{
    xstart = (int)(xstart / Tile_size);
    ystart = (int)(ystart / Tile_size);
    if (ystart < 0|| xstart < 0 ||  ystart > 200 || xstart > 200)
    {
        mlx_put_pixel(data->image_win,i,j,ft_pixel(0,0,0,255));
        return ;
    }
   
    if (wall_hit(xstart * Tile_size,ystart* Tile_size,data))
        mlx_put_pixel(data->image_win,j  ,i ,ft_pixel(106,50,159,255));
    else
        mlx_put_pixel(data->image_win,j ,i,ft_pixel(68,68,68,255));
    if (distance > 95)
        mlx_put_pixel(data->image_win,j  ,i ,ft_pixel(120,120,120,255));
}
void renderminimap(t_data *data)
{
    double xstart;
    double ystart;
    int i;
    int j;

    xstart = (data->player->px) - ((200)  / 2.0);
    ystart = (data->player->py) - ((200) / 2.0);
    i = 0;
    while (i < ((200)))
    {
        xstart = (data->player->px) - ((200)  / 2.0);
        j = 0;
        double d = 0;
        while (j <((200)))
        {
            d = sqrt(pow(j - 100, 2) +  pow(i - 100,2));
            if (d < 100)
            {
                draw_minimap(data,xstart,ystart,i,j,d);
            }
            j++;
            xstart++;
        }
        i++;
        ystart++;
    }
    draw_player(data,ft_pixel(255,0,0,255));
}

int width_size(char **str)
{
    size_t width;
    int i;

    (i = 1, width = ft_strlen(str[0]));
    while(str[i])
    {
        if (ft_strlen(str[i]) > width)
            width = ft_strlen(str[i]);
        i++;
    }
    return ((int)width);
}
int get_height(char **str)
{
    int i;

    i = -1;
    while(str[++i]);
    return (i);    
}
int hit_the_wall(double x,double y,t_data *data)
{
    int px;
    int py;

    px = x / Tile_size;
    py = y / Tile_size;
    if (px > (int)strlen(data->map[0]) || px < 0 || py < 0 || py > data->height)
        return (1);
    if ((((int)py / Tile_size) > 0) && (int)strlen(data->map[0]) > 0 && (((int)py / Tile_size) < (data->height))  &&  (((int)py / Tile_size) < (int)strlen(data->map[0])) &&  data->map[(int)py / Tile_size][(int)px / Tile_size] != '1')
        return (1);
    return (0);
}

void ft_renderplayer1(t_data *data)
{
    double mv;
    
    double px;
    double py;
    mv = data->player->side_direction * data->player->walkspeed;
    data->player->rotationAngle += data->player->turnDirection * data->player->turnspeed;
    px = data->player->px + cos(data->player->rotationAngle + M_PI_2)  * mv;
    py = data->player->py + sin(data->player->rotationAngle + M_PI_2) * mv;

   if ((((int)py / Tile_size) > 0) && (int)strlen(data->map[0]) > 0 && ((((int)py / Tile_size) < (data->height))  ||  (((int)py / Tile_size) < (int)data->width)) &&  data->map[(int)py / Tile_size][(int)px / Tile_size] != '1')
    {
            data->player->px = px;
            data->player->py = py;
    }
}
void ft_renderplayer(t_data *data)
{
    double mv;
    double px;
    double py;


    mv = data->player->walkDirection * data->player->walkspeed;
    data->player->rotationAngle += data->player->turnDirection * data->player->turnspeed;
   px = data->player->px + cos(data->player->rotationAngle)  * mv;
    py =data->player->py + sin(data->player->rotationAngle ) * mv;

    if ((((int)py / Tile_size) > 0) && (int)strlen(data->map[0]) > 0 && ((((int)py / Tile_size) < (data->height))  ||  (((int)py / Tile_size) < (int)data->width) )&&  data->map[(int)py / Tile_size][(int)px / Tile_size] != '1')
    {
            data->player->px = px;
            data->player->py = py;
    }
}
double check_angle(char c)
{
    if (c == 'N')
        return (3 * M_PI / 2);
    if (c == 'S')
        return (M_PI / 2);
    if (c == 'E')
        return (0);
    if (c == 'W')
        return (M_PI);
    return (0);
}
void    get_player_pos(t_data *data)
{
    int x;
    int y;

    y = -1;
    while (data->map[++y])
    {
        x = -1;
        while (data->map[y][++x])
        {
            if (strchr("NEWS", data->map[y][x]))
            {
                data->player->px = ((x * Tile_size) + (Tile_size /2));
                data->player->py = ((y * Tile_size) + (Tile_size / 2));
                data->player->rotationAngle = check_angle(data->map[y][x]);
            }
        }
    }
}

void ft_keyfunc_relesed(mlx_key_data_t keypress, t_data *data)
{
    if (keypress.key == MLX_KEY_W && keypress.action == MLX_RELEASE)
        data->player->walkDirection = 0;
     if (keypress.key == MLX_KEY_S && keypress.action == MLX_RELEASE)
        data->player->walkDirection = 0;
     if (keypress.key == MLX_KEY_A && keypress.action == MLX_RELEASE)
        data->player->side_direction = 0;
     if (keypress.key == MLX_KEY_D && keypress.action == MLX_RELEASE)
        data->player->side_direction = 0;
     if (keypress.key == MLX_KEY_LEFT && keypress.action == MLX_RELEASE)
        data->player->turnDirection = 0;
     if (keypress.key == MLX_KEY_RIGHT && keypress.action == MLX_RELEASE)
        data->player->turnDirection = 0;
    
}
void ft_keyfunc_pressed(mlx_key_data_t keypress, void *param)
{
    t_data *data;

    data = param;
    if (keypress.key == MLX_KEY_ESCAPE && keypress.action == MLX_PRESS)
        exit(0);
     if (keypress.key == MLX_KEY_W && keypress.action == MLX_PRESS)
        data->player->walkDirection = 1;
     if (keypress.key == MLX_KEY_S && keypress.action == MLX_PRESS)
        data->player->walkDirection = -1;
     if (keypress.key == MLX_KEY_A && keypress.action == MLX_PRESS)
        data->player->side_direction = -1;
     if (keypress.key == MLX_KEY_D && keypress.action == MLX_PRESS)
        data->player->side_direction = 1;
     if (keypress.key == MLX_KEY_LEFT && keypress.action == MLX_PRESS)
        data->player->turnDirection = -1;
     if (keypress.key == MLX_KEY_RIGHT && keypress.action == MLX_PRESS)
        data->player->turnDirection = 1;
    ft_keyfunc_relesed(keypress,data);
}

void fill_window(t_data *data)
{
    int i =0 ;
    int j;

    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            if (i > HEIGHT / 2)
                 mlx_put_pixel(data->image_win, j, i, ft_pixel(data->floor->r, data->floor->g,data->floor->b,255));
            else
                mlx_put_pixel(data->image_win, j, i, ft_pixel(data->ceiling->r,data->ceiling->g,data->ceiling->b,200));
                 j++;
        }
        i++;
    }
}
void mouse_move(t_data *data)
{
    int x;
    int y;

    mlx_get_mouse_pos(data->mlx,&x,&y);
    mlx_set_mouse_pos(data->mlx,WIDTH/2,HEIGHT/2);

    if (x > WIDTH/2)
        data->player->rotationAngle += 0.03;
    if (x < WIDTH/2)
        data->player->rotationAngle -= 0.03;
}

void ft_hook(void *param)
{
    t_data *data = param;
    if (data->player->walkDirection != 0 || data->player->turnDirection != 0)
        ft_renderplayer(data);
    if (data->player->side_direction != 0)
        ft_renderplayer1(data);
    mlx_delete_image(data->mlx,data->image_win);
    if (!(data->image_win = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return((void)EXIT_FAILURE);
	}
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    fill_window(data);
    mouse_move(data);
    castallrays(data);
    renderminimap(data);
}
int init_textures(t_data **data)
{
    (*data)->north = mlx_load_png((*data)->infos->north);
    if (!(*data)->north)
        return (printf("failed to load north texture"));
    (*data)->south = mlx_load_png((*data)->infos->south);
    if (!(*data)->south)
        return (printf("failed to load south texture"));
    (*data)->west = mlx_load_png((*data)->infos->west);
    if (!(*data)->west)
        return (printf("failed to load west texture"));
    (*data)->east = mlx_load_png((*data)->infos->east);
    if (!(*data)->east)
        return (printf("failed to load east texture"));
    return 0;
}
void init(t_data *data)
{
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    data->mlx = mlx_init(WIDTH,HEIGHT,"cub3d",true);
    if (!(data->mlx))
		return (puts(mlx_strerror(errno)),(void)EXIT_FAILURE);
    if (!(data->image_win = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return((void)EXIT_FAILURE);
	}
    if (init_textures(&data))
        exit (1);
    mlx_set_cursor_mode(data->mlx,MLX_MOUSE_HIDDEN);
    get_player_pos(data);
    data->no = img_to_double_pointer(data->north);
	data->so = img_to_double_pointer(data->south);
    data->we = img_to_double_pointer(data->west);
	data->ea = img_to_double_pointer(data->east);
    mlx_set_cursor_mode(data->mlx,MLX_MOUSE_HIDDEN);
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    mlx_key_hook(data->mlx,ft_keyfunc_pressed,data);
    mlx_loop_hook(data->mlx,ft_hook,data);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
}