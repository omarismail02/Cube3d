#include "../includes/parse.h"

void	print_error(char *str)
{
	printf("Error\n");
	printf("%s", str);
	printf("\n");
	exit(1);
}

void	free_tab(char **tab)
{
	char	**temp;

	temp = tab;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(tab);
}

int	file_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("file cannot be opened");
	return (fd);
}

void	free_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->rows)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void	element_inspector(char **map, int i, int j)
{
	if (map[i][j] == '0' || parse_camera(map[i][j], CAMERA) == 1)
		print_error("invalid map");
}
