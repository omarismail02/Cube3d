#include "../includes/struct.h"

t_motion	calculate_direction_vector(double degree, double distance)
{
	double		radians;
	t_motion	ray;

	radians = (degree / 180.0) * M_PI;
	ray.x = cos(radians) * distance;
	ray.y = sin(radians) * distance;
	return (ray);
}

void	plot_fov(t_info *data, t_ray_input *input)
{
	double		i;
	t_motion	ray;
	t_dda		result;
	t_motion	orientation;

	i = (-1 * (data->camera.fov / 2.0));
	while (i < (data->camera.fov / 2.0))
	{
		orientation = vrotate(data->camera.vector, data->camera.degree + i);
		result = dda(data->camera.position, orientation, i, data->map);
		ray = calculate_direction_vector(data->camera.degree + i, result.range);
		input->ray = ray;
		input->camerapos = data->camera.position;
		input->block_size = data->block_size;
		plot_ray(data->smallmap_data, *input, data->small_line_length,
			data->small_cd);
		i += 0.1;
	}
}

static void	init_ray_line_data(t_coordinates *start, t_coordinates *end,
		t_ray_input input)
{
	start->x = (int)(input.camerapos.x * input.block_size);
	start->y = (int)(input.camerapos.y * input.block_size);
	end->x = start->x + (int)(input.ray.x * input.block_size);
	end->y = start->y - (int)(input.ray.y * input.block_size);
}

void	plot_ray(char *img_data, t_ray_input input, int size_line, int bpp)
{
	t_coordinates	start;
	t_coordinates	end;
	t_image_data	data;

	init_ray_line_data(&start, &end, input);
	data.line_length = size_line;
	data.bpp = bpp;
	data.colour = RED;
	plot_line(start, end, img_data, &data);
}
