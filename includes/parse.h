#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# define CAMERA "WESN"
# define ROW " WESN01"

typedef struct d_data
{
	char			**map;
	int				paths_loaded;
	int				camera;
	int				direction;
	int				start;
	int				rows;
	unsigned char	ceil[3];
	unsigned char	floor[3];
	int				color_count;
	int				cols;
	char			*east;
	char			*west;
	char			*nor;
	char			*so;
	int				elements[6];
	double			pos[2];
}					t_data;

void				match_extension(char *str, char *str1);
int					parse_camera(char c, const char *tab);
int					parse_row(char *row);
void				free_map(t_data *data);
void				element_inspector(char **map, int i, int j);
int					read_input(t_data *data, char *file);
char				*path_load(int fd, t_data *data);
void				last_comma(char *str);
void				print_error(char *str);
void				free_tab(char **str);
int					file_open(char *file);
void				elements_check(int tab[]);
void				validate_map(int fd, char **line, t_data *data);
void				map_check(t_data *data);
void				render(t_data *data);

#endif