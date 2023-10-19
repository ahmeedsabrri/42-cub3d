/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/19 12:07:31 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void init(t_data *data);
//(255,255,0)yellow color
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}




void    draw_line(t_data *data, int lenght, double angle)
{
    int i;
    int j;
    i = 0;
    j = 0;
    double x ;
    double y;
    while (j <= 60)
    {
        while(i <= lenght)
        {
            x = sin((angle) *(PI / 180)) * i + (data->player.px + 5);    
            y = cos((angle) *(PI / 180)) * i + (data->player.py + 5);
            mlx_put_pixel(data->image_win, x + j, y + j, 0xFFFFFF);
            i++;
        }
        j++;
    }
}
void draw_player(t_data *data, uint32_t color)
{
    (void)color;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
                mlx_put_pixel(data->image_win, (data->player.px + i) * MINI_MAP_SCALE,(data->player.py + j) * MINI_MAP_SCALE, ft_pixel(255,255,255,255));
        }
    }
    draw_line(data,50 ,data->player.rotationAngle);
}
void draw_square(t_data *data, int y,int x, uint32_t color)
{
    (void)color;
    for (int i = 0; i < Tile_size - 1; i++)
        for (int j = 0; j < Tile_size - 1; j++)
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
////////////////////////////////////////////////////
void move_right(t_data *data,float *x,float *y)
{
    *x = ((cos(data->player.rotationAngle) * (PI /180)) * 5);
    *y = ((sin(data->player.rotationAngle) * (PI /180)) * 5);

    data->player.px += *x;
    data->player.py -= *y;
}
void move_left(t_data *data,float *x,float *y)
{
    *x = ((cos(data->player.rotationAngle) * (PI /180)) * 5);
    *y = ((sin(data->player.rotationAngle) * (PI /180)) * 5);

    data->player.px += *x;
    data->player.py -= *y;
}
void move_down(t_data *data,float *x,float *y)
{
    *x = ((cos(data->player.rotationAngle) - 90 * (PI /180)) * 5);
    *y = ((sin(data->player.rotationAngle) - 90 * (PI /180)) * 5);

    data->player.px += *x;
    data->player.py -= *y;
}
void move_up(t_data *data,float *x,float *y)
{
    *x = ((cos(data->player.rotationAngle) - 90 * (PI /180)) * 5);
    *y = ((sin(data->player.rotationAngle) - 90 * (PI /180)) * 5);

    data->player.px += *x;
    data->player.py -= *y;
}
////////////////////////////////////////////////////
void ft_hook(void *param)
{
    t_data *data = param;
    float x;
    float y;

    x = 0;
    y = 0;
    if (data->map[(((int)data->player.py + (int)y) / Tile_size)][((int)(data->player.px + (int)x) / Tile_size)] != '1')
    {
        if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
            mlx_close_window(data->mlx);
        if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
            move_up(data,&x,&y);
        else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
            move_down(data,&x,&y);
        else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
            move_left(data,&x,&y);
        else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
            move_right(data,&x,&y);
    }
    if (mlx_is_key_down(data->mlx,MLX_KEY_W))
        data->player.rotationAngle += 5;
    mlx_delete_image(data->mlx,data->image_win);
    if (!(data->image_win = mlx_new_image(data->mlx, 1027, 720)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return((void)EXIT_FAILURE);
	}
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    draw_map(data);
    draw_player(data,0xFFFF50);
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
                data->player.px = ((x * Tile_size) + (Tile_size /2));
                data->player.py = ((y * Tile_size) + (Tile_size / 2));
            }
        }
    }
    data->player.height = 5;
    data->player.width = 5;
    data->player.rotationAngle = PI / 2;
    data->player.walkDirection = 0;
    data->player.turnDirection = 0;
    data->player.turnDirection = 0;
    data->player.walkspeed = 100;
    data->player.turnspeed = 45 * (PI / 180);
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
    draw_map(data);
    draw_player(data,0xFFFF50);
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    mlx_loop_hook(data->mlx,ft_hook,data);

    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
}

int main()
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    char *map[] = {
        "111111111111",
        "100000000001",
        "100000000001",
        "100000000001",
        "10000000N001",
        "100000000001",
        "111111111111",
        NULL
    };
    data.map = map;
    init(&data);
    return (0);
}

