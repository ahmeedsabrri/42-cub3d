/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/11/03 21:52:26 by asabri           ###   ########.fr       */
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
//         if ((x1) > 1027 || (x1) < 0 || (y1) < 0 || (y1) > 720)
//             return;
//         mlx_put_pixel(data->image_win, round(x1), round(y1), color);
//         x1 += xIncrement;
//         y1 += yIncrement;
//         i++;
//     }
// }
void init(t_data *data);
//(255,255,0)yellow color
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_player(t_data *data, uint32_t color)
{
    (void)color;
    for (int i = 0; i < 360; i++)
        dda(data,data->player->px ,data->player->py ,data->player->px + (cos(i * PI/180) * 10),data->player->py + (sin(i * PI/180) * 10),ft_pixel(255,0,0,255));
    dda(data,data->player->px,data->player->py,data->player->px + (cos(data->player->rotationAngle) * 30),data->player->py + (sin(data->player->rotationAngle) * 30),ft_pixel(255,0,0,255));
}
void draw_square(t_data *data, int y,int x, uint32_t color)
{
    (void)color;
    for (int i = 0; i < Tile_size; i++)
        for (int j = 0; j < Tile_size; j++)
        {
            mlx_put_pixel(data->image_win, (x + i) * MINI_MAP_SCALE, (y + j) * MINI_MAP_SCALE, ft_pixel(color,color,color,color));
        }
}
void draw_map(t_data *data)
{
    int i;
    int j;

    i = -1;
    data->width = 0;
    data->height = 0;
    while (data->map[++i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] == '1')
                draw_square(data,i * Tile_size, j * Tile_size , 0x5a5a5a);
            else 
                draw_square(data,i * 64, j * 64, 0x808080);
            data->width++;
        }
        data->height++;
    }
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

   if ((((int)py / Tile_size) > 0) && (int)strlen(data->map[0]) > 0 && (((int)py / Tile_size) < (data->height))  &&  (((int)py / Tile_size) < (int)strlen(data->map[0])) &&  data->map[(int)py / Tile_size][(int)px / Tile_size] != '1')
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

    if ((((int)py / Tile_size) > 0) && (int)strlen(data->map[0]) > 0 && (((int)py / Tile_size) < (data->height))  &&  (((int)py / Tile_size) < (int)strlen(data->map[0])) &&  data->map[(int)py / Tile_size][(int)px / Tile_size] != '1')
    {
            data->player->px = px;
            data->player->py = py;
    }
}

void    get_player_pos(t_data *data)
{
    int x;
    int y;

    y = -1;
    while (data->map[++y]){
        x = -1;
        while (data->map[y][++x]){
            if (strchr("NEWS", data->map[y][x])){
                data->player->px = ((x * Tile_size) + (Tile_size /2));
                data->player->py = ((y * Tile_size) + (Tile_size / 2));
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

    while (i < 720)
    {
        j = 0;
        while (j < 1027)
        {
            if (i > 720 / 2)
                 mlx_put_pixel(data->image_win, j, i, ft_pixel(0, 0,0,255));
            else
                 mlx_put_pixel(data->image_win, j, i, ft_pixel(0, 255,0,255));
                 

                 j++;
        }
        i++;
    }
}

void ft_hook(void *param)
{
    t_data *data = param;
    // if (data->player->walkDirection != 0 || data->player->rotationAngle != 0)
    if (data->player->walkDirection != 0 || data->player->turnDirection != 0)
        ft_renderplayer(data);
    if (data->player->side_direction != 0)
        ft_renderplayer1(data);
        
    mlx_delete_image(data->mlx,data->image_win);
    if (!(data->image_win = mlx_new_image(data->mlx, 1027, 720)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return((void)EXIT_FAILURE);
	}
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    draw_map(data);
    fill_window(data);
    //  printf("angle : %lf",data->player->rotationAngle);
    // draw_player(data,0xFFFF50);
    castallrays(data);
}
void init(t_data *data)
{
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    data->mlx = mlx_init(1027,720,"cub3d",true);
    if (!(data->mlx))
		return (puts(mlx_strerror(errno)),(void)EXIT_FAILURE);
    if (!(data->image_win = mlx_new_image(data->mlx, 1027, 720)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return((void)EXIT_FAILURE);
	}
    get_player_pos(data);
    // draw_map(data);
    // draw_player(data,0xFFFF50);
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    mlx_key_hook(data->mlx,ft_keyfunc_pressed,data);
    mlx_loop_hook(data->mlx,ft_hook,data);

    
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
}


int main()
{
    t_data data;
    t_player player;
    
    memset(&data, 0, sizeof(t_data));
    char *map[] = {
        "111111111111",
        "100000000001",
        "100001000001",
        "100001000001",
        "10000110N001",
        "100000000001",
        "111111111111",
        NULL
    };
    player.height = 5;
    player.width = 5;
    player.rotationAngle = M_PI;
    player.side_direction = 0;
    player.walkDirection = 0; // up or down
    player.turnDirection = 0; // angle rotation 
    player.walkspeed = 5;
    player.turnspeed = 3.00 * (M_PI / 180.0);
    data.map = map;
    data.player = &player;
    init(&data);
    
    return (0);
}

