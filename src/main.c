/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/16 22:35:05 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// nt32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }
void draw_square(t_data *data, int y,int x, int color)
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            mlx_put_pixel(data->image_win, x + i, y + j, color);
        }
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
                draw_square(data,i * 64, j * 64,0x808080);
        }
    }
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
    draw(data);
    mlx_image_to_window(data->mlx, data->image_win, 0, 0);
    mlx_loop(data->mlx);
}

int main()
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    char *map[] = {
        "111111111111111",
        "100000000000001",
        "100000100000001",
        "100011100000001",
        "100000000000001",
        "100000000000001",
        "111111111111111",
        NULL
    };
    data.map = map;
    init(&data);
    return (0);
}

