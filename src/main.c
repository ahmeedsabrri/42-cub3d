/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/18 21:42:13 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//(255,255,0)yellow color
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void init(t_data *data);
void draw_player(t_data *data, uint32_t color)
{
    
    uint32_t c;
    
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            c= ft_pixel(
                color, // R
				color, // G
				color, // B
				color 
            );
                mlx_put_pixel(data->image_win, data->px + i, data->py + j, c);
        }
    }
}
void draw_square(t_data *data, int y,int x, uint32_t color)
{
    
    
    for (int i = 0; i < 63; i++)
        for (int j = 0; j < 63; j++)
        {
            mlx_put_pixel(data->image_win, x + i, y + j, color);
        }
}
void draw(t_data *data)
{
    int i;
    int j;

    i = -1;
    while (data->map[++i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] == '1')
                draw_square(data,i * 64, j * 64, 0x5a5a5a);
            else 
                draw_square(data,i * 64, j * 64, 0x808080);
        }
    }
    draw_player(data,0xFFFF50);
}
void ft_hook(void *param)
{
    t_data *data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
    const int y = mlx_is_key_down(data->mlx, MLX_KEY_UP) * -4 +
        mlx_is_key_down(data->mlx, MLX_KEY_DOWN) * 4;
    const int x = mlx_is_key_down(data->mlx, MLX_KEY_LEFT) * -4 +
        mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) * 4;
    if (data->map[((data->py + y) / 64)][((data->px + x) / 64)] != '1')
    {
        data->px += x;
        data->py += y;
    }
    mlx_delete_image(data->mlx,data->image_win);
    if (!(data->image_win = mlx_new_image(data->mlx, 1027, 720)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return((void)EXIT_FAILURE);
	}
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    draw(data);
}

void    get_player_pos(t_data *data)
{
    int x, y;
    y = -1;
    while (data->map[++y]){
        x = -1;
        while (data->map[y][++x]){
            if (strchr("NEWS", data->map[y][x])){
                data->px = ((x * 64) + (64 /2));
                data->py = ((y * 64) + (64 / 2));
            }
        }
    }
}

void init(t_data *data)
{
    get_player_pos(data);
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
    draw(data);
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
        "100000100001",
        "100011100101",
        "10001011N101",
        "100000000101",
        "111111111111",
        NULL
    };
    data.map = map;
    init(&data);
    return (0);
}

