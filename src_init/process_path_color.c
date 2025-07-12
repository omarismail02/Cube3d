#include "../includes/initialize.h"

static unsigned char	verify_color_elem(char *str)
{
	unsigned int	temp;
	char			*temp_str;
	char			*trim_str;

	temp = (unsigned int)ft_atoi(str);
	temp_str = ft_itoa(temp);
	trim_str = ft_strtrim(str, " ");
	if (ft_strncmp(trim_str, temp_str, ft_strlen(trim_str)) != 0)
		error_exit_input("invalid color input");
	if (temp > 255)
		error_exit_input("invalid color");
	free(temp_str);
	free(trim_str);
	return ((unsigned char)temp);
}

static void	process_color(char *line, unsigned char array[],
							t_data *data, int k)
{
	char	**split;

	if (data->nr_colors > 1)
		error_exit_input("too many colors");
	check_end_comma(line);
	split = ft_split((line + 1), ',');
	if (!split || !split[0] || !split[1] || !split[2])
		error_exit_input("failed ft_split");
	if (split[3] != NULL)
		error_exit_input("invalid color input");
	array[0] = verify_color_elem(split[0]);
	array[1] = verify_color_elem(split[1]);
	array[2] = verify_color_elem(split[2]);
	free_double(split);
	data->nr_colors++;
	data->true_input[k] = true;
}

static void	process_path(char *line, char **str, t_data *data, int k)
{
	char	**split;
	int		fd;

	if (*str != NULL)
		error_exit_input("double path");
	if (data->nr_paths > 3)
		error_exit_input("too many paths");
	split = ft_split(line + 2, ' ');
	if (!split || !split[0])
		error_exit_input("failed ft_split");
	if (split[1] != NULL)
		error_exit_input("invalid path input");
	check_extension(split[0], ".png");
	fd = open(split[0], O_RDONLY);
	if (fd == -1)
	{
		free_double(split);
		error_exit_input("invalid path");
	}
	*str = ft_strdup(split[0]);
	free_double(split);
	data->nr_paths++;
	data->true_input[k] = true;
}

static void	process_distribution(char *line, int j, t_data *data)
{
	if (line[j] == 'N' && line[j + 1] == 'O')
		process_path(line, &data->north, data, 0);
	else if (line[j] == 'S' && line[j + 1] == 'O')
		process_path(line, &data->south, data, 1);
	else if (line[j] == 'E' && line[j + 1] == 'A')
		process_path(line, &data->east, data, 2);
	else if (line[j] == 'W' && line[j + 1] == 'E')
		process_path(line, &data->west, data, 3);
	else if (line[j] == 'F')
		process_color(line, data->floor, data, 4);
	else if (line[j] == 'C')
		process_color(line, data->ceiling, data, 5);
}

char	*process_path_color(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	get_next_line(fd, &line);
	while (i < data->map_start - 1)
	{
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (line[j] != '\0')
			process_distribution(line, j, data);
		i++;
		free(line);
		get_next_line(fd, &line);
	}
	true_input_verify(data->true_input);
	return (line);
}
