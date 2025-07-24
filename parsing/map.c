#include "../includes/parse.h"

static void	memory_allocate(t_data *data)
{
	int	j;

	data->map = malloc(sizeof(char *) * data->rows);
	if (!data->map)
		print_error("failed malloc");
	j = 0;
	while (j < data->rows)
	{
		data->map[j] = malloc(sizeof(char) * (data->cols + 1));
		if (!data->map[j])
			print_error("malloc fail");
		data->map[j][data->cols] = '\0';
		j++;
	}
}

static void	copy_row(int i, char *line, t_data *data)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line);
	while (j < len)
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

void	validate_map(int fd, char **line, t_data *data)
{
	int	oct;
	int	i;

	i = 0;
	memory_allocate(data);
	copy_row(i, *line, data);
	i++;
	free(*line);
	oct = get_next_line(fd, line);
	while (oct > 0 && i < data->rows)
	{
		if (i < data->rows && parse_row(*line) == 1)
			print_error("error in row");
		copy_row(i, *line, data);
		i++;
		free(*line);
		oct = get_next_line(fd, line);
	}
	if (parse_row(*line) == 1)
		print_error("error in row");
	copy_row(i, *line, data);
}
