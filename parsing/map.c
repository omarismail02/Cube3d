#include "../includes/parse.h"

static void	memory_allocate(t_data *data)
{
	int	i;

	data->map = malloc(sizeof(char *) * data->rows);
	if (!data->map)
		print_error("failed malloc");
	i = 0;
	while (i < data->rows)
	{
		data->map[i] = malloc(sizeof(char) * (data->cols + 1));
		if (!data->map[i])
			print_error("malloc fail");
		data->map[i][data->cols] = '\0';
		i++;
	}
}

static void	copy_row(int i, char *line, t_data *data)
{
	int	j;
	int	size;

	j = 0;
	size = ft_strlen(line);
	while (j < size)
	{
		data->map[i][j] = (line)[j];
		j++;
	}
	while (j < data->cols)
	{
		data->map[i][j] = ' ';
		j++;
	}
}

void	check_store_map(int fd, char **line, t_data *data)
{
	int	i;
	int	bytes;

	i = 0;
	memory_allocate(data);
	copy_row(i, *line, data);
	i++;
	free(*line);
	bytes = get_next_line(fd, line);
	while (bytes > 0 && i < data->rows)
	{
		if (i < data->rows && check_row_map(*line) == 1)
			print_error("invalid map row");
		copy_row(i, *line, data);
		i++;
		free(*line);
		bytes = get_next_line(fd, line);
	}
	if (check_row_map(*line) == 1)
		print_error("invalid map row");
	copy_row(i, *line, data);
}
