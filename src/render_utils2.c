/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:20:43 by abberkac          #+#    #+#             */
/*   Updated: 2023/11/23 13:20:15 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	png_delete(t_data *data)
{
	mlx_delete_texture(data->north);
	mlx_delete_texture(data->south);
	mlx_delete_texture(data->west);
	mlx_delete_texture(data->east);
}

void	init_textures2(t_data *data)
{
	data->no = png_to_dpointer(data->north);
	data->so = png_to_dpointer(data->south);
	data->we = png_to_dpointer(data->west);
	data->ea = png_to_dpointer(data->east);
}

int	init_textures(t_data **data)
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
	return (0);
}

void	init(t_data *data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!(data->mlx))
		return (puts(mlx_strerror(errno)), (void)EXIT_FAILURE);
	data->image_win = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!(data->image_win))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return ((void)EXIT_FAILURE);
	}
	if (init_textures(&data))
		exit(1);
	init_textures2(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	get_player_pos(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(data->mlx, data->image_win, 0, 0);
	mlx_key_hook(data->mlx, ft_keyfunc_pressed, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	png_delete(data);
}
