/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:04:34 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:04:36 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

static void	texture_init(t_data *data, t_info *context)
{
	int	i;

	context->bitmap[0] = mlx_xpm_file_to_image(context->mlx, data->east,
			&context->bitmap_width[0], &context->bitmap_height[0]);
	context->bitmap[1] = mlx_xpm_file_to_image(context->mlx, data->so,
			&context->bitmap_width[1], &context->bitmap_height[1]);
	context->bitmap[2] = mlx_xpm_file_to_image(context->mlx, data->west,
			&context->bitmap_width[2], &context->bitmap_height[2]);
	context->bitmap[3] = mlx_xpm_file_to_image(context->mlx, data->nor,
			&context->bitmap_width[3], &context->bitmap_height[3]);
	free(data->west);
	free(data->nor);
	free(data->so);
	free(data->east);
	i = 0;
	while (i < 4)
	{
		if (!context->bitmap[i])
			print_error("Texture could not be loaded.");
		context->bitmap_data[i] = mlx_get_data_addr(context->bitmap[i],
				&context->bitmap_cd[i], &context->line_length[i],
				&context->byte_order[i]);
		++i;
	}
}

static void	fill_var(t_info *data)
{
	data->camera.vector.x = 1.0;
	data->camera.vector.y = 0.0;
	data->camera.speed = 5;
	data->camera.fov = 70;
	data->mov_angle = 3.0;
}

int	init_state(t_data *data, t_info *context, void *mlx)
{
	context->mlx = mlx;
	context->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!context->img)
		return (-1);
	context->img_data = mlx_get_data_addr(context->img, &context->color_depth,
			&context->line_len, &context->order);
	if (!context->img_data)
		return (-1);
	context->img_width = WIDTH;
	context->img_height = HEIGHT;
	texture_init(data, context);
	context->camera.position.x = data->pos[1];
	context->camera.position.y = data->pos[0];
	context->camera.degree = data->direction;
	fill_var(context);
	context->map = data->map;
	if (!context->map)
		return (-1);
	context->range_x = data->cols;
	context->range_y = data->rows;
	context->col_ceil = create_colour(data->ceil[0], data->ceil[1],
			data->ceil[2], 255);
	context->col_floor = create_colour(data->floor[0], data->floor[1],
			data->floor[2], 255);
	return (1);
}
