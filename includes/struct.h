/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:25:24 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 16:25:25 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "parse.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>

// Window resolution definition
# define WIDTH 1100
# define HEIGHT 600
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREY 0x808080
# define RED 0xFF0000
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define PINK 0xFFC0CB
# define BROWN 0xA52A2A
# define GOLD 0xFFD700
# define NAVY 0x000080
# define TEAL 0x008080
# define OLIVE 0x808000
# define DARKGREY 0xA9A9A9
# define LIGHTGREY 0xD3D3D3
# define SKYBLUE 0x87CEEB
# define TURQUOISE 0x40E0D0
# define INDIGO 0x4B0082
# define YELLOW 0xFFFF00
# define GREEN 0x008000
# define LAWNGREEN 0x7CFC00
# define BLUE 0x0000FF
# define LIGHTSKYBLUE 0x87CEFA
# define MINIMAP 200

typedef struct r_raygrid_data
{
	double					dda_increment_x;
	double					dda_increment_y;
	double					ray_len_x;
	double					ray_len_y;
	int						x;
	int						y;
	int						step_of_x;
	int						step_of_y;
}							t_raygrid_data;

typedef struct s_img_info
{
	char					*img_data;
	int						size_line;
	int						bpp;
	int						color;
}							t_img_info;

typedef struct s_clear_info
{
	char					*img_data;
	int						width;
	int						height;
	int						size_line;
	int						bpp;
}							t_clear_info;

typedef struct m_motion
{
	double					x;
	double					y;
}							t_motion;

enum						e_direction
{
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3
};

typedef struct c_camera
{
	t_motion				position;
	t_motion				vector;
	double					degree;
	unsigned int			speed;
	unsigned int			fov;
}							t_camera;

typedef struct d_dda
{
	enum e_direction		dir;
	double					position;
	double					view_dist;
	double					range;
}							t_dda;

typedef struct c_coordinates
{
	int						x;
	int						y;
}							t_coordinates;

typedef struct s_info
{
	t_camera				camera;

	void					*mlx;
	void					*win;

	void					*img;
	char					*img_data;
	int						order;
	unsigned int			img_width;
	unsigned int			img_height;
	int						color_depth;
	int						line_len;
	void					*bitmap[4];
	char					*bitmap_data[4];
	int						bitmap_width[4];
	int						bitmap_height[4];
	int						bitmap_cd[4];
	int						line_length[4];
	int						byte_order[4];

	char					**map;
	double					mov_angle;

	unsigned int			col_floor;
	unsigned int			col_ceil;
	unsigned int			top;
	unsigned int			bottom;
	unsigned int			range_x;
	unsigned int			range_y;
	unsigned int			block_size;
	void					*wall;
	double					step;
	double					bitmap_begin;
	double					whp;
	void					*small_map;
	char					*smallmap_data;
	int						small_cd;
	int						small_line_length;
	int						small_order;
	int						prev_mouse_x;
	double					mouse_sensitivity;
}							t_info;

typedef struct s_colors
{
	union
	{
		unsigned int		colors;
		struct
		{
			unsigned char	m;
			unsigned char	n;
			unsigned char	a;
			unsigned char	o;
		};
	};
}							t_colors;

typedef struct s_image_data
{
	char					*buffer;
	int						line_length;
	int						bpp;
	unsigned int			colour;
}							t_image_data;

typedef struct s_ray_input
{
	t_motion				ray;
	t_motion				camerapos;
	unsigned int			block_size;
}							t_ray_input;

int							init_state(t_data *data, t_info *gamedata,
								void *mlx);
t_motion					vadd(t_motion vec1, t_motion vec2);
t_motion					vsub(t_motion vec1, t_motion vec2);
t_coordinates				vec2pos(t_motion vec);
t_motion					vrotate(t_motion vect, double degree);
void						plot_line(t_coordinates po, t_coordinates po1,
								char *image, t_image_data *data);
void						plot_line_horizontal(t_coordinates po,
								t_coordinates po1, char *image,
								t_image_data *data);
void						init(t_img_info *info, t_clear_info *data,
								t_ray_input *input, t_image_data *image);
void						plot_line_vertical(t_coordinates po,
								t_coordinates po1, char *image,
								t_image_data *data);
long						abs_int(int number);
double						absolute(double number);
double						normalize_angle(double angle);
void						clear_fu(t_clear_info *info, t_info *data);
t_dda						dda(t_motion pos_camera, t_motion ray, double angle,
								char **map);
void						plot_point(t_img_info *info, unsigned int x,
								unsigned int y, unsigned int colour);
void						clear_image(t_clear_info *info);
int							begin_small_map(t_info *gamedata,
								unsigned int max_pixels_minimap);
void						plot_camera_heading(t_clear_info *data1,
								t_motion camerapos, t_motion headingline);
void						plot_camera_square(t_img_info *info, int px,
								int py);

void						plot_camera(t_clear_info *data1, t_camera camera,
								unsigned int bloc_size);
void						plot_map(t_info *data);
void						plot_ray(char *img_data, t_ray_input input,
								int size_line, int bpp);
t_motion					calculate_direction_vector(double degree,
								double distance);
void						plot_fov(t_info *data, t_ray_input *input);

void						init_projection(t_info *data);

unsigned int				get_colour_from_xpm(char *img_data, int x, int y,
								t_image_data *data);
unsigned int				adjust_brightness(unsigned int colour,
								double percentage);
unsigned int				create_colour(unsigned char r, unsigned char g,
								unsigned char b, unsigned char a);
void						render(t_data *data);
int							close_window(void *param);
int							key_press(int keycode, t_info *data);
int							loop_hook(t_info *data);
int							close_window(void *param);

#endif
