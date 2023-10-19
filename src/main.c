/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/19 15:34:21 by asabri           ###   ########.fr       */
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
    i = 0;
    double x ;
    double y; 
    while(i < lenght)
    {
       x = sin(angle *(PI / 180)) * i + (data->player->px + 5);    
       y = cos(angle *(PI / 180)) * i + (data->player->py + 5);
       mlx_put_pixel(data->image_win, x, y, 0xFFFFFF);
       i++;
    }
}
void draw_player(t_data *data, uint32_t color)
{
    (void)color;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
                mlx_put_pixel(data->image_win, (data->player->px + i) * MINI_MAP_SCALE,(data->player->py + j) * MINI_MAP_SCALE, ft_pixel(255,255,255,255));
                printf("here\n");
        }
    }
    draw_line(data,50 ,data->player->rotationAngle);
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

void ft_renderplayer1(t_data *data)
{
    float mv;

    mv = data->player->side_direction * data->player->walkspeed;
    data->player->rotationAngle += data->player->turnDirection * data->player->turnspeed;
    data->player->px += cos(data->player->rotationAngle + M_PI_2)  * mv;
    data->player->py += sin(data->player->rotationAngle + M_PI_2) * mv;
}
void ft_renderplayer(t_data *data)
{
    float mv;

    mv = data->player->walkDirection * data->player->walkspeed;
    data->player->rotationAngle += data->player->turnDirection * data->player->turnspeed;
    data->player->px += cos(data->player->rotationAngle) * mv;
    data->player->py += sin(data->player->rotationAngle) * mv;
}
void ft_hook(void *param)
{
    t_data *data = param;
    if (data->player->walkDirection != 0 || data->player->turnDirection != 0)
        ft_renderplayer(data);
   else if (data->player->side_direction != 0)
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
        data->player->walkDirection = -1;
     if (keypress.key == MLX_KEY_S && keypress.action == MLX_PRESS)
        data->player->walkDirection = 1;
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
        "100000000001",
        "100000000001",
        "10000000N001",
        "100000000001",
        "111111111111",
        NULL
    };
    player.height = 5;
    player.width = 5;
    player.rotationAngle = PI / 2;
    player.side_direction = 0;
    player.walkDirection = 0; // up or down
    player.turnDirection = 0; // angle rotation 
    player.walkspeed = 5;
    player.turnspeed = 45 * (PI / 180);
    data.map = map;
    data.player = &player;
    init(&data);
    return (0);
}

