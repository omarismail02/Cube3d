#include "../includes/struct.h"
#include <string.h>

void	plot_point(t_img_info *info, unsigned int x, unsigned int y,
		unsigned int colour)
{
	unsigned char	*dst;

	if (!info || !info->img_data)
		return ;
	if (x >= 1920 || y >= 1080)
		return ;
	dst = (unsigned char *)info->img_data + y * info->size_line + x * (info->bpp
			/ 8);
	if (info->bpp == 32)
		*(unsigned int *)dst = colour;
	else if (info->bpp == 24)
	{
		dst[0] = colour & 0xFF;
		dst[1] = (colour >> 8) & 0xFF;
		dst[2] = (colour >> 16) & 0xFF;
	}
}

void	clear_image(t_clear_info *info)
{
	int	y;

	if (!info || !info->img_data)
		return ;
	y = 0;
	while (y < info->height)
	{
		memset(info->img_data + y * info->size_line, 0, info->size_line);
		y++;
	}
}
