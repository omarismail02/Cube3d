#ifndef STRUCT_H
# define STRUCT_H

#include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include "parse.h"

// Window resolution definition
# define WIDTH 1100
# define HEIGHT 600
# define WHITE           0xFFFFFF
# define BLACK           0x000000
# define GREY            0x808080
# define RED             0xFF0000
# define ORANGE          0xFFA500
# define PURPLE          0x800080
# define CYAN            0x00FFFF
# define MAGENTA         0xFF00FF
# define PINK            0xFFC0CB
# define BROWN           0xA52A2A
# define GOLD            0xFFD700
# define NAVY            0x000080
# define TEAL            0x008080
# define OLIVE           0x808000
# define DARKGREY        0xA9A9A9
# define LIGHTGREY       0xD3D3D3
# define SKYBLUE         0x87CEEB
# define TURQUOISE       0x40E0D0
# define INDIGO          0x4B0082
# define YELLOW          0xFFFF00
# define GREEN           0x008000
# define LAWNGREEN       0x7CFC00
# define BLUE            0x0000FF
# define LIGHTSKYBLUE    0x87CEFA
# define MINIMAP 200

typedef struct r_raygrid_data {
	double dda_increment_x;
	double dda_increment_y;
	double ray_len_x;
	double ray_len_y;
	int x;
	int y;
	int step_of_x;
	int step_of_y;
} t_raygrid_data;

typedef struct m_motion {
	double x;
	double y;
} t_motion;

enum direction {
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3
};

typedef struct c_camera {
	t_motion	position;
	t_motion	vector;
	double		degree;
	unsigned int	speed;
	unsigned int	fov;
} t_camera;

typedef struct d_dda {
	enum direction	dir;
	double		position;
	double		view_dist;
	double		range;
} t_dda;

typedef struct c_coordinates {
	int x;
	int y;
} t_coordinates;

typedef struct s_info {
	t_camera	player;

	void		*mlx;
	void		*win;

	void		*img;
	char		*img_data;
	int			bpp;
	int			line_len;
	int			endian;
	unsigned int img_width;
	unsigned int img_height;

	void		*texture[4];
	char		*texture_data[4];
	int			tex_width[4];
	int			tex_height[4];
	int			texture_bpp[4];
	int			texture_line_len[4];
	int			texture_endian[4];

	char		**map;
	double		rotation_angle;

	unsigned int floor_colour;
	unsigned int ceiling_colour;
	unsigned int top;
	unsigned int bottom;
	unsigned int map_width;
	unsigned int map_height;
	unsigned int mini_pixelsize;
	void 		*wall;
	double 		step;
	double 		tex_start;
	double 		wall_height_perc;
	void		*imgmini;
	char		*imgmini_data;
	int			mini_bpp;
	int			mini_line_len;
	int			mini_endian;
	int			prev_mouse_x;
	double		mouse_sensitivity;
} t_info;

typedef struct s_colors {
	union {
		unsigned int colors;
		struct {
			unsigned char m;
			unsigned char n;
			unsigned char a;
			unsigned char o;
		};
	};
} t_colors;

int				init_gamestate(t_data *data, t_info *gamedata, void *mlx);

t_coordinates			vec_to_coor(t_motion vec);
t_motion		add_vectors(t_motion vec1, t_motion vec2);
t_motion		subtract_vectors(t_motion vec1, t_motion vec2);
t_motion		rotate_vector(t_motion vect, double degree);

void plot_line(t_coordinates po, t_coordinates po1, char *image, int leng,
	 int bpp, unsigned int colour);

void			plot_line_horizontal(t_coordinates point1, t_coordinates point2, 
					char *img_data, int size_line, int bpp, unsigned int colour);
void			plot_line_vertical(t_coordinates point1, t_coordinates point2, 
					char *img_data, int size_line, int bpp, unsigned int colour);
long			abs_int(int number);

double	absolute(double number);

t_dda			apply_dda(t_motion pos_player, t_motion ray, double angle, 
					char **map);

void			draw_pixel(char *img_data, int size_line, int bpp, 
					unsigned int x, unsigned int y, unsigned int colour);
void			clear_image(char *img_data, int width, int height, 
					int size_line, int bpp);

int				init_minimap(t_info *gamedata, unsigned int max_pixels_minimap);
void			draw_player(char *img_data, t_camera player, 
					unsigned int pixelsize, int size_line, int bpp);
void			draw_map(t_info *data);
void			draw_ray(char *img_data, t_motion ray, t_motion playerpos, 
					unsigned int pixelsize, int size_line, int bpp);
t_motion		calc_ray_vector(double degree, double distance);
void			draw_viewing_cone(t_info *data);


void			create_projection(t_info *data);

unsigned int	get_colour_from_xpm(char *img_data, int x, int y, 
					int size_line, int bpp);
unsigned char	get_colour_value(unsigned int colour, char colourpart);
unsigned int	adjust_brightness(unsigned int colour, double percentage);
unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b, 
					unsigned char a);

void			render(t_data *data);
int 			close_window(void *param);

int				key_press(int keycode, t_info *data);
int				loop_hook(t_info *data);
int				close_window(void *param);

#endif