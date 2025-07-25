/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:10:05 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:10:06 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	row_verification(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == '0' || parse_camera(map[i][j], CAMERA) == 1)
			print_error("invalid map");
		j++;
	}
}

static void	process_camera(int i, int j, t_data *data)
{
	if (data->camera == 1)
		print_error("camera is unique");
	data->camera = 1;
	if (data->map[i][j] == 'N')
		data->direction = 90;
	if (data->map[i][j] == 'S')
		data->direction = 270;
	if (data->map[i][j] == 'E')
		data->direction = 0;
	if (data->map[i][j] == 'W')
		data->direction = 180;
	data->pos[0] = i + 0.5;
	data->pos[1] = j + 0.5;
}

static void	camera_walk(char **map, int i, t_data *data)
{
	int	j;

	j = 0;
	element_inspector(data->map, i, j);
	j++;
	while (j < data->cols - 1)
	{
		if (map[i][j] == '0' || parse_camera(map[i][j], CAMERA) == 1)
		{
			if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
				map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
				map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ' ||
				map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
				print_error("invalid map");
			if (parse_camera(map[i][j], CAMERA) == 1)
				process_camera(i, j, data);
		}
		j++;
	}
	element_inspector(data->map, i, j);
}

void	map_check(t_data *data)
{
	int	j;

	j = 0;
	row_verification(data->map, j);
	j++;
	while (j < (data->rows - 1))
	{
		camera_walk(data->map, j, data);
		j++;
	}
	row_verification(data->map, j);
	if (data->camera == 0)
		print_error("no camera on the map");
}
