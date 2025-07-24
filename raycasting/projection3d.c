#include "../includes/struct.h"

static void	plot_floor_ceil(t_info *data, unsigned int top, unsigned int bottom,
		unsigned int x)
{
	t_coordinates	top_ceil;
	t_coordinates	bottom_ceil;
	t_coordinates	top_floor;
	t_coordinates	bottom_floor;
	t_image_data	data1;

	data1.line_length = data->line_len;
	data1.bpp = data->color_depth;
	data1.colour = data->col_ceil;
	top_ceil.x = x;
	top_ceil.y = 0;
	bottom_ceil.x = x;
	bottom_ceil.y = top - 1;
	top_floor.x = x;
	top_floor.y = bottom + 1;
	bottom_floor.x = x;
	bottom_floor.y = data->img_height - 1;
	plot_line(top_ceil, bottom_ceil, data->img_data, &data1);
	data1.colour = data->col_floor;
	plot_line(top_floor, bottom_floor, data->img_data, &data1);
}

static unsigned int	sample_texel(t_info *data, unsigned int i, unsigned int x,
		unsigned int y)
{
	unsigned int	offset;
	unsigned char	*dst;

	if (x >= (unsigned int)data->bitmap_width[i]
		|| y >= (unsigned int)data->bitmap_height[i])
		return (0x00000000);
	offset = y * data->line_length[i] + x * (data->bitmap_cd[i] / 8);
	dst = (unsigned char *)data->bitmap_data[i] + offset;
	return (*(unsigned int *)dst);
}

static void	plot_wall_slice_column(t_info *data, unsigned int x, t_dda *result,
		t_info *vars)
{
	unsigned int	y;
	unsigned int	colour;
	t_img_info		info;

	y = 0;
	info.img_data = data->img_data;
	info.size_line = data->line_len;
	info.bpp = data->color_depth;
	while (y <= vars->bottom - vars->top)
	{
		if (result->dir == EAST || result->dir == NORTH)
			colour = sample_texel(data, result->dir, (unsigned int)((1.0
							- result->position)
						* data->bitmap_width[result->dir]),
					(unsigned int)(vars->bitmap_begin + y * vars->step));
		else
			colour = sample_texel(data, result->dir,
					(unsigned int)(result->position
						* data->bitmap_width[result->dir]),
					(unsigned int)(vars->bitmap_begin + y * vars->step));
		colour = adjust_brightness(colour, vars->whp);
		plot_point(&info, x, y + vars->top, colour);
		y++;
	}
}

static void	plot_wall_slice(t_info *data, unsigned int x,
		unsigned int wall_height, t_dda *result)
{
	t_info	vars;

	vars.wall = data->bitmap[result->dir];
	vars.step = 1.0 * data->bitmap_height[result->dir] / wall_height;
	if (wall_height > data->img_height)
	{
		vars.top = 0;
		vars.bottom = data->img_height - 1;
		vars.bitmap_begin = (((1 - (1.0 * data->img_height / wall_height))
					/ 2.0) * data->bitmap_height[result->dir]);
	}
	else
	{
		vars.top = (data->img_height - wall_height) / 2;
		vars.bottom = (data->img_height + wall_height) / 2;
		vars.bitmap_begin = 0.0;
	}
	vars.whp = 1.0 * wall_height / data->img_height;
	plot_wall_slice_column(data, x, result, &vars);
	plot_floor_ceil(data, vars.top, vars.bottom, x);
}

void	init_projection(t_info *data)
{
	t_dda			dda_result;
	unsigned int	x;
	double			deg;
	double			ps;
	unsigned int	column_height;

	x = 0;
	while (x < data->img_width)
	{
		ps = tanf(((data->camera.fov / 2.0) / 180) * M_PI);
		deg = (atanf(-ps + ((2.0 * ps * x) / data->img_width)) * 180) / M_PI;
		dda_result = dda(data->camera.position, vrotate(data->camera.vector,
					data->camera.degree - deg), deg, data->map);
		column_height = (unsigned int)(data->img_height / dda_result.view_dist);
		plot_wall_slice(data, x, column_height, &dda_result);
		x++;
	}
}
