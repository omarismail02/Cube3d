#ifndef INITIALIZE_H
# define INITIALIZE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

# include "libft.h"
# include "get_next_line.h"

# define MAP_ROW " 01NSEW"
# define MAP_PLAYER "NSEW"

typedef struct s_data
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	unsigned char	ceiling[3];
	unsigned char	floor[3];
	bool			true_input[6];		
	char			**map;
	int				nr_paths;
	int				nr_colors;
	int				player;
	double			player_pos[2];
	int				player_direction;
	int				map_start;
	int				map_rows;
	int				map_columns;
}				t_data;

int		open_fd(char *file);
int		check_row_map(char *line);
void	check_extension(char *str1, char *str2);
int		check_player(char c, const char *array);
int		process_input(char *file, t_data *data);
char	*process_path_color(int fd, t_data *data);
void	check_end_comma(char *str);
void	true_input_verify(bool array[]);
void	check_store_map(int fd, char **line, t_data *data);
void	check_map_validity( t_data *data);

void	render(t_data *data);

void	free_double(char **str);
void	free_map(t_data *data);

void	error_exit_input(char *str);

#endif