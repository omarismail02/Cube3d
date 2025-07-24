#include "../includes/struct.h"

int	begin_small_map(t_info *data, unsigned int max_size)
{
	unsigned int	width;
	unsigned int	height;

	if (data->range_x > data->range_y)
	{
		data->block_size = max_size / data->range_x;
		width = data->block_size * data->range_x;
		height = data->block_size * data->range_y;
	}
	else
	{
		data->block_size = max_size / data->range_y;
		height = data->block_size * data->range_y;
		width = data->block_size * data->range_x;
	}
	data->small_map = mlx_new_image(data->mlx, width, height);
	if (data->small_map == NULL)
		return (-1);
	data->smallmap_data = mlx_get_data_addr(data->small_map, &data->small_cd,
			&data->small_line_length, &data->small_order);
	return (1);
}

void	plot_camera(t_clear_info *data1, t_camera camera,
		unsigned int bloc_size)
{
	int			px;
	int			py;
	t_motion	camerapos;
	t_motion	headingline;
	t_img_info	info;

	info.img_data = data1->img_data;
	info.size_line = data1->size_line;
	info.bpp = data1->bpp;
	info.color = WHITE;
	px = (int)(camera.position.x * bloc_size);
	py = (int)(camera.position.y * bloc_size);
	plot_camera_square(&info, px, py);
	camerapos.x = px;
	camerapos.y = py;
	headingline = vrotate(camera.vector, camera.degree);
	headingline.x *= 10;
	headingline.y *= 10;
	plot_camera_heading(data1, camerapos, headingline);
}

static void	plot_wall(t_img_info *data, unsigned int x, unsigned int y,
		unsigned int bloc_size)
{
	unsigned int	x_coo;
	unsigned int	y_coo;
	t_img_info		info;

	info.img_data = data->img_data;
	info.size_line = data->size_line;
	info.bpp = data->bpp;
	x_coo = x;
	while (x_coo < x + bloc_size - 1)
	{
		y_coo = y;
		while (y_coo < y + bloc_size - 1)
		{
			plot_point(&info, x_coo, y_coo, WHITE);
			++y_coo;
		}
		++x_coo;
	}
}

static void	plot_floor(t_img_info *data, unsigned int x, unsigned int y,
		unsigned int bloc_size)
{
	unsigned int	x_coo;
	unsigned int	y_coo;
	t_img_info		info;

	info.img_data = data->img_data;
	info.size_line = data->size_line;
	info.bpp = data->bpp;
	x_coo = x;
	while (x_coo < x + bloc_size)
	{
		y_coo = y;
		while (y_coo < y + bloc_size)
		{
			plot_point(&info, x_coo, y_coo, GREY);
			++y_coo;
		}
		++x_coo;
	}
}

void	plot_map(t_info *data)
{
	unsigned int	bloc_size;
	unsigned int	y;
	unsigned int	x;
	t_img_info		info;

	bloc_size = data->block_size;
	info.img_data = data->smallmap_data;
	info.size_line = data->small_line_length;
	info.bpp = data->small_cd;
	y = 0;
	while (y < data->range_y)
	{
		x = 0;
		while (x < data->range_x)
		{
			if (data->map[y][x] == '1')
				plot_wall(&info, x * bloc_size, y * bloc_size, bloc_size);
			else
				plot_floor(&info, x * bloc_size, y * bloc_size, bloc_size);
			++x;
		}
		++y;
	}
}
