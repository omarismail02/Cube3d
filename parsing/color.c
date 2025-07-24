#include "../includes/parse.h"

static unsigned char	color_input(char *str)
{
	unsigned int	temp;
	char			*trim_str;
	int				i;

	trim_str = ft_strtrim(str, " ");
	if (!trim_str || trim_str[0] == '\0')
		print_error("invalid color input");
	i = 0;
	while (trim_str[i])
	{
		if (!ft_isdigit(trim_str[i]))
			print_error("invalid color input");
		i++;
	}
	temp = (unsigned int)ft_atoi(trim_str);
	if (temp > 255)
		print_error("invalid color");
	free(trim_str);
	return ((unsigned char)temp);
}

static void	load_input_color(t_data *data, unsigned char array[], char *line,
		int q)
{
	char	**tab;

	if (data->color_count > 1)
		print_error("too many colors");
	last_comma(line);
	tab = ft_split((line + 1), ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		print_error("failed ft_tab");
	if (tab[3] != NULL)
		print_error("invalid color input");
	array[0] = color_input(tab[0]);
	array[1] = color_input(tab[1]);
	array[2] = color_input(tab[2]);
	free_tab(tab);
	data->elements[q] = 1;
	data->color_count++;
}

static void	load_texture(char *line, char **str, t_data *data, int q)
{
	char	**tab;
	int		fd;

	if (*str != NULL)
		print_error("path already exists");
	if (data->paths_loaded > 3)
		print_error("number of paths should be 4");
	tab = ft_split(line + 2, ' ');
	if (!tab || !tab[0])
		print_error("failed to split");
	if (tab[1] != NULL)
		print_error("path is not valid");
	match_extension(tab[0], ".xpm");
	fd = open(tab[0], O_RDONLY);
	if (fd == -1)
	{
		free_tab(tab);
		print_error("path is not valid");
	}
	*str = ft_strdup(tab[0]);
	free_tab(tab);
	data->paths_loaded++;
	data->elements[q] = 1;
}

static void	parse_element(t_data *data, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O')
		load_texture(line, &data->nor, data, 0);
	else if (line[j] == 'S' && line[j + 1] == 'O')
		load_texture(line, &data->so, data, 1);
	else if (line[j] == 'E' && line[j + 1] == 'A')
		load_texture(line, &data->east, data, 2);
	else if (line[j] == 'W' && line[j + 1] == 'E')
		load_texture(line, &data->west, data, 3);
	else if (line[j] == 'F')
		load_input_color(data, data->floor, line, 4);
	else if (line[j] == 'C')
		load_input_color(data, data->ceil, line, 5);
}

char	*path_load(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	get_next_line(fd, &line);
	while (i < data->start - 1)
	{
		j = 0;
		while (line[j] == '\t' || line[j] == ' ')
			j++;
		if (line[j] != '\0')
			parse_element(data, line, j);
		i++;
		free(line);
		get_next_line(fd, &line);
	}
	elements_check(data->elements);
	return (line);
}
