#include "../includes/struct.h"

unsigned int adjust_brightness(unsigned int colour, double percent)
{
	t_colors color;

	color.colors = colour;
	if (percent < 1.0)
	{
		color.o = (unsigned char)((percent) * color.o);
		color.n = (unsigned char)((percent) * color.n);
		color.m = (unsigned char)((percent) * color.m);
	}
	return (color.colors);
}

unsigned int get_colour_from_xpm(char *img_data, int x, int y,
								int size_line, int bpp)
{
	unsigned int color;
	unsigned char *pixel;

	if (!img_data || x < 0 || y < 0)
		return (0x00000000);

	pixel = (unsigned char *)img_data + y * size_line + x * (bpp / 8);
	color = 0;
	if (bpp == 32)
	{
		color = *(unsigned int *)pixel;
	}
	else if (bpp == 24)
	{
		// Assuming little endian: RGB in three bytes
		color = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16) | (0xFF << 24);
	}
	return (color);
}

unsigned int create_colour(unsigned char r, unsigned char g, unsigned char b,
						   unsigned char a)
{
	// Format: 0xAARRGGBB for minilibx-linux (usually 32bpp ARGB)
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
