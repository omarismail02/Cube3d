/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:01:17 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:01:21 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

unsigned int	adjust_brightness(unsigned int colour, double percent)
{
	t_colors	color;

	color.colors = colour;
	if (percent < 1.0)
	{
		color.o = (unsigned char)((percent) * color.o);
		color.n = (unsigned char)((percent) * color.n);
		color.m = (unsigned char)((percent) * color.m);
	}
	return (color.colors);
}

unsigned int	get_colour_from_xpm(char *img_data, int x, int y,
		t_image_data *data)
{
	unsigned int	color;
	unsigned char	*pixel;

	if (!img_data || x < 0 || y < 0)
		return (0x00000000);
	pixel = (unsigned char *)img_data + y * data->line_length + x * (data->bpp
			/ 8);
	color = 0;
	if (data->bpp == 32)
	{
		color = *(unsigned int *)pixel;
	}
	else if (data->bpp == 24)
	{
		color = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16) | (0xFF << 24);
	}
	return (color);
}

unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

double	normalize_angle(double angle)
{
	angle = angle - ((int)(angle / 360) *360);
	if (angle < 0)
		angle += 360;
	return (angle);
}

void	clear_fu(t_clear_info *info, t_info *data)
{
	info->img_data = data->img_data;
	info->width = WIDTH;
	info->height = HEIGHT;
	info->size_line = data->line_len;
	info->bpp = data->color_depth;
}
