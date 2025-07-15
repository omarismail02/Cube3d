#include "../includes/parse.h"

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
	int	count;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (line[i] != '\0')
	{
		j = 0;
		count = 0;
		while (ROW[j] != '\0')
		{
			if (line[i] == ROW[j])
				count = 1;
			j++;
		}
		if (count == 0)
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
		print_error("invalid color input, too many commas");
}

void	check_end_comma(char *str)
{
	int	i;
	int	len;

	i = 1;
	count_commas(str);
	while (str[i] != '\0' && ft_isdigit((int)str[i]) == 0)
	{
		if (str[i] == ',')
			print_error("invalid color input, too many commas");
		i++;
	}
	len = ft_strlen(str);
	while (len > -1 && ft_isdigit(str[len]) == 0)
	{
		if (str[len] == ',' && str[len - 1] != ',')
			print_error("invalid color input, too many commas");
		len--;
	}
}

void	true_input_verify(bool tab[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (tab[i] == false)
			print_error("should have 4 texture and 2 color inputs");
		i++;
	}
}
