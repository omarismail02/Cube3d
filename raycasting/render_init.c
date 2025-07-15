#include "../includes/struct.h"

static void load_textures(t_data *data, t_info *gamedata)
{
    int i;

    // Load XPM textures and store image pointers
    gamedata->texture[0] = mlx_xpm_file_to_image(gamedata->mlx, data->east,
        &gamedata->tex_width[0], &gamedata->tex_height[0]);
    gamedata->texture[1] = mlx_xpm_file_to_image(gamedata->mlx, data->south,
        &gamedata->tex_width[1], &gamedata->tex_height[1]);
    gamedata->texture[2] = mlx_xpm_file_to_image(gamedata->mlx, data->west,
        &gamedata->tex_width[2], &gamedata->tex_height[2]);
    gamedata->texture[3] = mlx_xpm_file_to_image(gamedata->mlx, data->nor,
        &gamedata->tex_width[3], &gamedata->tex_height[3]);

    // Free texture path strings if dynamically allocated
    free(data->west);
    free(data->nor);
    free(data->south);
    free(data->east);

    // Get data address for each texture
    i = 0;
    while (i < 4)
    {
        if (!gamedata->texture[i])
            print_error("Texture could not be loaded.");
        gamedata->texture_data[i] = mlx_get_data_addr(gamedata->texture[i],
            &gamedata->texture_bpp[i], &gamedata->texture_line_len[i],
            &gamedata->texture_endian[i]);
        ++i;
    }
}

int init_gamestate(t_data *data, t_info *gamedata, void *mlx)
{
    gamedata->mlx = mlx;

    // Create main image and get its data address
    gamedata->img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!gamedata->img)
        return (-1);
    if(gamedata->img != NULL)
        printf("hello");
    gamedata->img_data = mlx_get_data_addr(
        gamedata->img, &gamedata->bpp, &gamedata->line_len, &gamedata->endian);
    if (!gamedata->img_data)
        return (-1);
    
    // Set image dimensions
    gamedata->img_width = WIDTH;
    gamedata->img_height = HEIGHT;

    // Load textures and their data
    load_textures(data, gamedata);

    // Initialize player info
    gamedata->player.position.x = data->pos[1];
    gamedata->player.position.y = data->pos[0];
    gamedata->player.degree = data->direction;
    gamedata->player.vector.x = 1.0;
    gamedata->player.vector.y = 0.0;
    gamedata->player.speed = 5;
    gamedata->player.fov = 70;

    gamedata->rotation_angle = 3.0;

    // Map info
    gamedata->map = data->map;
    if (!gamedata->map)
        return (-1);
    gamedata->map_width = data->cols;
    gamedata->map_height = data->rows;

    // Colors
    gamedata->ceiling_colour = create_colour(data->ceiling[0],
        data->ceiling[1], data->ceiling[2], 255);
    gamedata->floor_colour = create_colour(data->floor[0],
        data->floor[1], data->floor[2], 255);

    return (1);
}