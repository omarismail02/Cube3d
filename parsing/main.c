#include "../includes/parse.h"

static void	initialization(t_data *data, int i)
{
	data->paths_loaded = 0;
	data->start = 0;
	data->color_count = 0;
	data->rows = 0;
	data->cols = 0;
	data->camera = 0;
	data->direction = -1;
	data->start = 0;
	data->nor = NULL;
	data->so = NULL;
	data->east = NULL;
	data->west = NULL;
	data->rows = 0;
	while (i < 6)
	{
		data->elements[i] = 0;
		i++;
	}
}

void	match_extension(char *str, char *str1)
{
	int	len;
	int	len1;
	int	i;

	i = 1;
	len = ft_strlen(str);
	len1 = ft_strlen(str1);
	while (len - i > -1 && len1 - i > -1)
	{
		if (str[len - i] == str1[len1 - i])
		{
			if (len1 - i == 0)
				break ;
			i++;
		}
		else
			print_error("wxtension is not valid");
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (ft_strlen(argv[1]) == 0)
	{
		printf("No map to read\n");
		return (1);
	}
	match_extension(argv[1], ".cub");
	initialization(&data, 0);
	read_input(&data, argv[1]);
	render(&data);
	free_map(&data);
	return (0);
}
