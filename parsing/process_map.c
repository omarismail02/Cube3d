#include "../includes/initialize.h"

static void	allocate_memory_map(t_data *data)
{
	int	i;

	data->map = malloc(sizeof(char *) * data->map_rows);
	if (!data->map)
		error_exit_input("failed malloc");
	i = 0;
	while (i < data->map_rows)
	{
		data->map[i] = malloc(sizeof(char) * (data->map_columns + 1));
		if (!data->map[i])
			error_exit_input("malloc fail");
		data->map[i][data->map_columns] = '\0';
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
	while (j < data->map_columns)
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
	allocate_memory_map(data);
	copy_row(i, *line, data);
	i++;
	free(*line);
	bytes = get_next_line(fd, line);
	while (bytes > 0 && i < data->map_rows)
	{
		if (i < data->map_rows && check_row_map(*line) == 1)
			error_exit_input("invalid map row");
		copy_row(i, *line, data);
		i++;
		free(*line);
		bytes = get_next_line(fd, line);
	}
	if (check_row_map(*line) == 1)
		error_exit_input("invalid map row");
	copy_row(i, *line, data);
}
