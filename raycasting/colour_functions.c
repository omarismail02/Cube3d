#include "../includes/render.h"

unsigned int	grading_colour(unsigned int colour, double percentage)
{
	t_rgba	color;

	color.rgba = colour;
	if (percentage < 1.0)
	{
		color.r = (unsigned char)((percentage) * color.r);
		color.g = (unsigned char)((percentage) * color.g);
		color.b = (unsigned char)((percentage) * color.b);
	}
	return (color.rgba);
}

unsigned int	get_colour_png(mlx_texture_t *png, unsigned int x
					, unsigned int y)
{
	unsigned int	offset;
	unsigned char	*dst;

	if (x < png->width && y < png->height)
	{
		offset = y * (png->width * 4) + x * 4;
		dst = png->pixels + offset;
		return (*(unsigned int *) dst);
	}
	return (0X00000000);
}

unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b
				, unsigned char a)
{
	return ((unsigned int)(a << 24 | b << 16 | g << 8 | r));
}
