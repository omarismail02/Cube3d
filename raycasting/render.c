/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:04:55 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:04:57 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

static void	resolve_movement(t_info *data, double angle)
{
	t_dda		result;
	t_motion	mov;

	mov = vrotate(data->camera.vector, data->camera.degree + angle);
	result = dda(data->camera.position, mov, data->camera.degree + angle,
			data->map);
	if (result.range > 0.1)
	{
		data->camera.position.x += mov.x * 0.01 * data->camera.speed;
		data->camera.position.y += mov.y * 0.01 * data->camera.speed;
	}
}

int	key_press(int keycode, t_info *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (keycode == 65363)
		data->camera.degree = normalize_angle(data->camera.degree
				- data->mov_angle);
	if (keycode == 65361)
		data->camera.degree = normalize_angle(data->camera.degree
				+ data->mov_angle);
	if (keycode == 119)
		resolve_movement(data, 0.0);
	if (keycode == 100)
		resolve_movement(data, 270.0);
	if (keycode == 97)
		resolve_movement(data, 90.0);
	if (keycode == 115)
		resolve_movement(data, 180.0);
	return (0);
}

int	loop_hook(t_info *data)
{
	t_ray_input		input;
	t_clear_info	clear;
	t_img_info		info;
	t_image_data	image;

	init(&info, &clear, &input, &image);
	clear_image(&clear);
	clear_fu(&clear, data);
	init_projection(data);
	clear.img_data = data->smallmap_data;
	clear.width = data->block_size * data->range_x;
	clear.height = data->block_size * data->range_y;
	clear.size_line = data->small_line_length;
	clear.bpp = data->small_cd;
	clear_image(&clear);
	plot_map(data);
	plot_fov(data, &input);
	plot_camera(&clear, data->camera, data->block_size);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->small_map, WIDTH
		- data->block_size * data->range_x, HEIGHT - data->block_size
		* data->range_y);
	return (0);
}

void	helper_function(t_info *gamedata)
{
	mlx_put_image_to_window(gamedata->mlx, gamedata->win, gamedata->small_map,
		WIDTH - gamedata->block_size * gamedata->range_x, HEIGHT
		- gamedata->block_size * gamedata->range_y);
	mlx_hook(gamedata->win, 2, 1L << 0, key_press, gamedata);
	mlx_hook(gamedata->win, 17, 0, close_window, NULL);
	mlx_loop_hook(gamedata->mlx, loop_hook, gamedata);
}

void	render(t_data *data)
{
	t_info			gamedata;
	t_ray_input		input;
	t_clear_info	clear;

	gamedata.mlx = mlx_init();
	if (!gamedata.mlx)
		print_error("Could not initialize mlx");
	gamedata.win = mlx_new_window(gamedata.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!gamedata.win)
		print_error("Could not create window");
	if (init_state(data, &gamedata, gamedata.mlx) == -1)
		print_error("Failed to init game state");
	if (begin_small_map(&gamedata, MINIMAP) == -1)
		print_error("Failed to init minimap");
	init_projection(&gamedata);
	plot_map(&gamedata);
	plot_fov(&gamedata, &input);
	clear.img_data = gamedata.img_data;
	clear.size_line = gamedata.small_line_length;
	clear.bpp = gamedata.small_cd;
	plot_camera(&clear, gamedata.camera, gamedata.block_size);
	mlx_put_image_to_window(gamedata.mlx, gamedata.win, gamedata.img, 0, 0);
	helper_function(&gamedata);
	mlx_loop(gamedata.mlx);
}
