/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:09:33 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:09:34 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	line_size(char *line, t_data *data)
{
	int	len;

	len = ft_strlen(line);
	if (len != 0)
		data->rows++;
	if (len > data->cols)
		data->cols = len;
}

static void	rows_num(int fd, char **line, int i, t_data *data)
{
	int	oct;

	data->rows++;
	data->cols = ft_strlen(*line);
	free(*line);
	oct = get_next_line(fd, line);
	while (oct > 0)
	{
		line_size(*line, data);
		free(*line);
		oct = get_next_line(fd, line);
	}
	if (*line[i] != '\0')
		line_size(*line, data);
	free(*line);
}

static void	map_begin(int fd, t_data *da)
{
	int		i;
	char	*li;
	int		oct;

	oct = get_next_line(fd, &li);
	i = 0;
	while (oct > 0)
	{
		if ((li[i] == 'N' && li[i + 1] == 'O')
			|| (li[i] == 'S' && li[i + 1] == 'O')
			|| (li[i] == 'E' && li[i + 1] == 'A')
			|| (li[i] == 'W' && li[i + 1] == 'E')
			|| li[i] == 'F' || li[i] == 'C' || li[i] == '\0')
			da->start++;
		else if (parse_row(li) == 0)
			break ;
		else
			print_error("map or input invalid");
		free(li);
		oct = get_next_line(fd, &li);
	}
	da->start++;
	rows_num(fd, &li, i, da);
}

int	read_input(t_data *data, char *file)
{
	int		fd;
	char	*line;

	fd = file_open(file);
	map_begin(fd, data);
	close(fd);
	fd = file_open(file);
	line = path_load(fd, data);
	validate_map(fd, &line, data);
	free(line);
	close(fd);
	map_check(data);
	return (0);
}
