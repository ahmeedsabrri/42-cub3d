/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:17:47 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/23 17:14:17 by abberkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_keyfunc_relesed(mlx_key_data_t keypress, t_data *data)
{
	if (keypress.key == MLX_KEY_W && keypress.action == MLX_RELEASE)
		data->player->walk_direct = 0;
	if (keypress.key == MLX_KEY_S && keypress.action == MLX_RELEASE)
		data->player->walk_direct = 0;
	if (keypress.key == MLX_KEY_A && keypress.action == MLX_RELEASE)
		data->player->side_direction = 0;
	if (keypress.key == MLX_KEY_D && keypress.action == MLX_RELEASE)
		data->player->side_direction = 0;
	if (keypress.key == MLX_KEY_LEFT && keypress.action == MLX_RELEASE)
		data->player->turn_direct = 0;
	if (keypress.key == MLX_KEY_RIGHT && keypress.action == MLX_RELEASE)
		data->player->turn_direct = 0;
}

void	ft_keyfunc_pressed(mlx_key_data_t keypress, void *param)
{
	t_data	*data;

	data = param;
	if (keypress.key == MLX_KEY_ESCAPE && keypress.action == MLX_PRESS)
		exit(0);
	if (keypress.key == MLX_KEY_W && keypress.action == MLX_PRESS)
		data->player->walk_direct = 1;
	if (keypress.key == MLX_KEY_S && keypress.action == MLX_PRESS)
		data->player->walk_direct = -1;
	if (keypress.key == MLX_KEY_A && keypress.action == MLX_PRESS)
		data->player->side_direction = -1;
	if (keypress.key == MLX_KEY_D && keypress.action == MLX_PRESS)
		data->player->side_direction = 1;
	if (keypress.key == MLX_KEY_LEFT && keypress.action == MLX_PRESS)
		data->player->turn_direct = -1;
	if (keypress.key == MLX_KEY_RIGHT && keypress.action == MLX_PRESS)
		data->player->turn_direct = 1;
	ft_keyfunc_relesed(keypress, data);
}

void	fill_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i > HEIGHT / 2)
				mlx_put_pixel(data->image_win, j, i, ft_pixel(data->floor->r, \
							data->floor->g, data->floor->b, 255));
			else
				mlx_put_pixel(data->image_win, j, i, ft_pixel(data->ceiling->r, \
							data->ceiling->g, data->ceiling->b, 200));
			j++;
		}
		i++;
	}
}

void	mouse_move(t_data *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	if (x > WIDTH / 2)
		data->player->rotat_angle += 0.03;
	if (x < WIDTH / 2)
		data->player->rotat_angle -= 0.03;
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (data->player->walk_direct != 0 || data->player->turn_direct != 0)
		ft_renderplayer(data);
	if (data->player->side_direction != 0)
		ft_renderplayer1(data);
	mlx_delete_image(data->mlx, data->image_win);
	data->image_win = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!(data->image_win))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return ((void)EXIT_FAILURE);
	}
	mlx_image_to_window(data->mlx, data->image_win, 0, 0);
	fill_window(data);
	mouse_move(data);
	wall_projection(data);
	renderminimap(data);
}
