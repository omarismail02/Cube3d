/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:09:02 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:09:06 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	parse_camera(char c, const char *tab)
{
	int	j;

	j = 0;
	while (tab[j] != '\0')
	{
		if (tab[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int	parse_row(char *row)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	if (row[i] == '\0')
		return (1);
	while (row[i] != '\0')
	{
		j = 0;
		count = 0;
		while (ROW[j] != '\0')
		{
			if (row[i] == ROW[j])
				count = 1;
			j++;
		}
		if (count == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	nb_comma(char *str)
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
		print_error("number of commas should be 2 only");
}

void	last_comma(char *str)
{
	int	i;
	int	len;

	i = 1;
	nb_comma(str);
	while (str[i] != '\0' && ft_isdigit((int)str[i]) == 0)
	{
		if (str[i] == ',')
			print_error("number of commas should be 2 only");
		i++;
	}
	len = ft_strlen(str);
	while (len > -1 && ft_isdigit(str[len]) == 0)
	{
		if (str[len] == ',' && str[len - 1] != ',')
			print_error("number of commas should be 2 only");
		len--;
	}
}

void	elements_check(int tab[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (tab[i] == 0)
			print_error("should have 4 texture and 2 color inputs");
		i++;
	}
}
