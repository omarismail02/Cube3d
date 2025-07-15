#include "../includes/parse.h"

static void	count_line(char *line, t_data *data)
{
	int	row_size;

	row_size = ft_strlen(line);
	if (row_size > data->cols)
		data->cols = row_size;
	if (row_size != 0)
		data->rows++;
}

static void	count_rows(int fd, char **line, int i, t_data *data)
{
	int	bytes;

	data->rows++;
	data->cols = ft_strlen(*line);
	free(*line);
	bytes = get_next_line(fd, line);
	while (bytes > 0)
	{
		count_line(*line, data);
		free(*line);
		bytes = get_next_line(fd, line);
	}
	if (*line[i] != '\0')
		count_line(*line, data);
	free(*line);
}

static void	map_begin(int fd, t_data *da)
{
	int		i;
	char	*li;
	int		bytes;

	i = 0;
	bytes = get_next_line(fd, &li);
	while (bytes > 0)
	{
		if ((li[i] == 'N' && li[i + 1] == 'O')
			|| (li[i] == 'S' && li[i + 1] == 'O')
			|| (li[i] == 'E' && li[i + 1] == 'A')
			|| (li[i] == 'W' && li[i + 1] == 'E')
			|| li[i] == 'F' || li[i] == 'C' || li[i] == '\0')
			da->start++;
		else if (check_row_map(li) == 0)
			break ;
		else
			print_error("invalid input/map row");
		free(li);
		bytes = get_next_line(fd, &li);
	}
	da->start++;
	count_rows(fd, &li, i, da);
}

int	process_input(char *file, t_data *data)
{
	char	*line;
	int		fd;

	fd = open_fd(file);
	map_begin(fd, data);
	close(fd);
	fd = open_fd(file);
	line = path_load(fd, data);
	check_store_map(fd, &line, data);
	free(line);
	close(fd);
	check_map_validity(data);
	return (0);
}
