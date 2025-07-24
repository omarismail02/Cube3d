#include "../includes/struct.h"

double	absolute(double number)
{
	if (number < 0)
		return (-1 * number);
	return (number);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
}

void	plot_camera_square(t_img_info *info, int px, int py)
{
	unsigned int	x;
	unsigned int	y;
	int				draw_x;
	int				draw_y;

	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			draw_x = px - 1 + x;
			draw_y = py - 1 + y;
			if (draw_x >= 0 && draw_y >= 0)
				plot_point(info, (unsigned int)draw_x, (unsigned int)draw_y,
					WHITE);
			x++;
		}
		y++;
	}
}

void	plot_camera_heading(t_clear_info *data1, t_motion camerapos,
		t_motion headingline)
{
	t_image_data	data;

	data.colour = WHITE;
	plot_line(vec2pos(camerapos), vec2pos(vadd(camerapos, headingline)),
		data1->img_data, &data);
}
