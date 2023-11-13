/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 01:33:47 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/13 04:01:42 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int main(int ac, char **av)
{
    t_data  *data;
    t_player *player;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (1);
    player = (t_player *)malloc(sizeof(t_player));
    if (!player)
        return (1);
    if (parsing(ac, av, data))
		return (1);
    data->HEIGHTt = get_HEIGHTt(data->map);
    data->width = width_size(data->map);
    player->rotationAngle = PI / 2;
    player->side_direction = 0;
    player->walkDirection = 0; // up or down
    player->turnDirection = 0; // angle rotation 
    player->walkspeed = 2;
    player->turnspeed = 3.00 * (M_PI / 180.0);
    data->player = player;
    init(data);
    return (0);
}