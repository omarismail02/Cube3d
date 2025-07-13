#include "../includes/initialize.h"

int	check_player(char c, const char *array)
{
	int	i;

	i = 0;
	while (array[i] != '\0')
	{
		if (array[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_row_map(char *line)
{
	int	i;
	int	j;
	int	exists;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (line[i] != '\0')
	{
		j = 0;
		exists = 0;
		while (MAP_ROW[j] != '\0')
		{
			if (line[i] == MAP_ROW[j])
				exists = 1;
			j++;
		}
		if (exists == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	count_commas(char *str)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		error_exit_input("invalid color input, too many commas");
}

void	check_end_comma(char *str)
{
	int	length;
	int	i;

	count_commas(str);
	i = 1;
	while (str[i] != '\0' && ft_isdigit((int)str[i]) == 0)
	{
		if (str[i] == ',')
			error_exit_input("invalid color input, too many commas");
		i++;
	}
	length = ft_strlen(str);
	while (length > -1 && ft_isdigit(str[length]) == 0)
	{
		if (str[length] == ',' && str[length - 1] != ',')
			error_exit_input("invalid color input, too many commas");
		length--;
	}
}


void	true_input_verify(bool array[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (array[i] == false)
			error_exit_input("missing path/color input");
		i++;
	}
}
