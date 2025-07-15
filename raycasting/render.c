#include "../includes/struct.h"

// Forward declaration
static void process_movement_input(t_info *data, double angle);

int key_press(int keycode, t_info *data)
{
	if (keycode == 65307) // ESC
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (keycode == 65363) // RIGHT arrow
		data->player.degree = fmod(data->player.degree - data->rotation_angle + 360, 360);
	if (keycode == 65361) // LEFT arrow
		data->player.degree = fmod(data->player.degree + data->rotation_angle, 360);
	if (keycode == 119) // W
		process_movement_input(data, 0.0);
	if (keycode == 100) // D
		process_movement_input(data, 270.0);
	if (keycode == 97) // A
		process_movement_input(data, 90.0);
	if (keycode == 115) // S
		process_movement_input(data, 180.0);
	return (0);
}

// Movement logic
static void process_movement_input(t_info *data, double angle)
{
	t_motion mov_vector;
	t_dda result;

	mov_vector = rotate_vector(data->player.vector, data->player.degree + angle);
	result = apply_dda(data->player.position, mov_vector, data->player.degree + angle, data->map);
	if (result.range > 0.1)
	{
		data->player.position.x += mov_vector.x * 0.01 * data->player.speed;
		data->player.position.y += mov_vector.y * 0.01 * data->player.speed;
	}
}

// Loop redraw
int loop_hook(t_info *data)
{
	clear_image(data->img_data, WIDTH, HEIGHT, data->line_len, data->bpp);
	create_projection(data);
	clear_image(data->imgmini_data, data->mini_pixelsize * data->map_width,
		data->mini_pixelsize * data->map_height, data->mini_line_len, data->mini_bpp);
	draw_map(data);
	draw_viewing_cone(data);
	draw_player(data->imgmini_data, data->player, data->mini_pixelsize,
		data->mini_line_len, data->mini_bpp);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->imgmini,
		WIDTH - data->mini_pixelsize * data->map_width,
		HEIGHT - data->mini_pixelsize * data->map_height);
	return (0);
}

// Main render function
void render(t_data *data)
{
	t_info gamedata;

	gamedata.mlx = mlx_init();
	if (!gamedata.mlx)
		print_error("Could not initialize mlx");

	gamedata.win = mlx_new_window(gamedata.mlx, WIDTH, HEIGHT, "Cub3D");

	if (!gamedata.win)
		print_error("Could not create window");

	if (init_gamestate(data, &gamedata, gamedata.mlx) == -1)
		print_error("Failed to init game state");

	if (init_minimap(&gamedata, MINIMAP) == -1)
		print_error("Failed to init minimap");

	create_projection(&gamedata);
	draw_map(&gamedata);
	draw_viewing_cone(&gamedata);
	draw_player(gamedata.imgmini_data, gamedata.player, gamedata.mini_pixelsize,
		gamedata.mini_line_len, gamedata.mini_bpp);

	mlx_put_image_to_window(gamedata.mlx, gamedata.win, gamedata.img, 0, 0);
	mlx_put_image_to_window(gamedata.mlx, gamedata.win, gamedata.imgmini,
		WIDTH - gamedata.mini_pixelsize * gamedata.map_width,
		HEIGHT - gamedata.mini_pixelsize * gamedata.map_height);

	mlx_hook(gamedata.win, 2, 1L << 0, key_press, &gamedata);
	mlx_hook(gamedata.win, 17, 0, close_window, NULL);
	mlx_loop_hook(gamedata.mlx, loop_hook, &gamedata);
	mlx_loop(gamedata.mlx);
}
