/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:55:33 by asabri            #+#    #+#             */
/*   Updated: 2023/10/16 21:35:44 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// nt32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }
void init(t_data *data)
{
    data->mlx = mlx_init(1027,720,"cub3d",true);
    if (!(data->mlx))
		return (puts(mlx_strerror(errno)),(void)EXIT_FAILURE);
    mlx_loop(data->mlx);
}
int main()
{
    t_data data;
    char *map[] = {
        "111111111111111",
        "100000000000001",
        "100000100000001",
        "10001110000N001",
        "100000000000001",
        "100000000000001",
        "111111111111111",
        NULL
    };
    data.map = map;
    init(&data);
    return (0);
}