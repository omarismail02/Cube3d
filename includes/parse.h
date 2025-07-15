#ifndef PARSE_H
# define PARRSE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "get_next_line.h"

# define PLAYER "WESN"
# define ROW " WESN01"

typedef struct s_data
{
	unsigned char	ceiling[3];
	unsigned char	floor[3];
	bool			true_input[6];		
	char			**map;
	int				nr_paths;
	int				nr_colors;
	int				player;
	int				direction;
	int				start;
	int				rows;
	int				cols;
	char			*nor;
	char			*south;
	char			*east;
	char			*west;
	double			pos[2];
}				t_data;

int		check_row_map(char *line);
void	check_extension(char *str1, char *str2);
int		check_player(char c, const char *array);
int		process_input(char *file, t_data *data);
char	*path_load(int fd, t_data *data);
void	check_end_comma(char *str);
void	true_input_verify(bool array[]);
void	check_store_map(int fd, char **line, t_data *data);
void	check_map_validity( t_data *data);

void	render(t_data *data);
void	print_error(char *str);
void	free_tab(char **str);
int		open_fd(char *file);
void	free_map(t_data *data);
void	element_inspector(char **map, int i, int j);

#endif