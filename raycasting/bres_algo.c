#include "../includes/struct.h"

void	plot_line(t_coordinates po, t_coordinates po1, char *image,
		t_image_data *data)
{
	if (abs_int(po1.y - po.y) < abs_int(po1.x - po.x))
	{
		if (po.x > po1.x)
			plot_line_horizontal(po1, po, image, data);
		else
			plot_line_horizontal(po, po1, image, data);
	}
	else
	{
		if (po.y > po1.y)
			plot_line_vertical(po1, po, image, data);
		else
			plot_line_vertical(po, po1, image, data);
	}
}

static void	fun(t_coordinates *po, int *diff, int delta[2], int dir)
{
	if (*diff > 0)
	{
		if (dir == 0)
			po->y += delta[1];
		else
			po->x += delta[1];
		*diff += 2 * (delta[0] - delta[2]);
	}
	else
		*diff += 2 * delta[0];
	if (dir == 0)
		po->x++;
	else
		po->y++;
}

void	plot_line_horizontal(t_coordinates po, t_coordinates po1, char *image,
		t_image_data *data)
{
	t_img_info	info;
	int			v[4];
	int			delta[3];

	info.img_data = image;
	info.size_line = data->line_length;
	info.bpp = data->bpp;
	v[0] = po1.x - po.x;
	v[1] = po1.y - po.y;
	if (v[1] < 0)
		v[2] = -1;
	else
		v[2] = 1;
	if (v[1] < 0)
		v[1] = -v[1];
	v[3] = (2 * v[1]) - v[0];
	delta[0] = v[1];
	delta[1] = v[2];
	delta[2] = v[0];
	while (po.x <= po1.x)
	{
		plot_point(&info, po.x, po.y, data->colour);
		fun(&po, &v[3], delta, 0);
	}
}

void	plot_line_vertical(t_coordinates po, t_coordinates po1, char *image,
		t_image_data *data)
{
	t_img_info	info;
	int			v[4];
	int			delta[3];

	info.img_data = image;
	info.size_line = data->line_length;
	info.bpp = data->bpp;
	v[0] = po1.y - po.y;
	v[1] = po1.x - po.x;
	if (v[1] < 0)
		v[2] = -1;
	else
		v[2] = 1;
	if (v[1] < 0)
		v[1] = -v[1];
	v[3] = (2 * v[1]) - v[0];
	delta[0] = v[1];
	delta[1] = v[2];
	delta[2] = v[0];
	while (po.y <= po1.y)
	{
		plot_point(&info, po.x, po.y, data->colour);
		fun(&po, &v[3], delta, 1);
	}
}

long	abs_int(int number)
{
	if (number >= 0)
		return ((long)number);
	else
		return ((long)-1 * number);
}
