#include "../includes/parse.h"

static void	row_verification(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == '0' || check_player(map[i][j], PLAYER) == 1)
			print_error("invalid map");
		j++;
	}
}

static void	process_player(int i, int j, t_data *data)
{
	if (data->player == 1)
		print_error("too many players");
	data->player = 1;
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

static void	middle_section(char **map, int i, t_data *data)
{
	int	j;

	j = 0;
	element_inspector(data->map, i, j);
	j++;
	while (j < data->cols - 1)
	{
		if (map[i][j] == '0' || check_player(map[i][j], PLAYER) == 1)
		{
			if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
				map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
				map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ' ||
				map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
				print_error("invalid map");
			if (check_player(map[i][j], PLAYER) == 1)
				process_player(i, j, data);
		}
		j++;
	}
	element_inspector(data->map, i, j);
}

void	check_map_validity(t_data *data)
{
	int	i;

	i = 0;
	row_verification(data->map, i);
	i++;
	while (i < (data->rows - 1))
	{
		middle_section(data->map, i, data);
		i++;
	}
	row_verification(data->map, i);
	if (data->player == 0)
		print_error("no player on the map");
}
