#include "../includes/struct.h"

int init_minimap(t_info *gamedata, unsigned int max_pixels_minimap)
{
    unsigned int miniwidth;
    unsigned int miniheight;

    if (gamedata->map_width > gamedata->map_height)
    {
        gamedata->mini_pixelsize = max_pixels_minimap / gamedata->map_width;
        miniwidth = gamedata->mini_pixelsize * gamedata->map_width;
        miniheight = gamedata->mini_pixelsize * gamedata->map_height;
    }
    else
    {
        gamedata->mini_pixelsize = max_pixels_minimap / gamedata->map_height;
        miniheight = gamedata->mini_pixelsize * gamedata->map_height;
        miniwidth = gamedata->mini_pixelsize * gamedata->map_width;
    }
    
    gamedata->imgmini = mlx_new_image(gamedata->mlx, miniwidth, miniheight);
    if (gamedata->imgmini == NULL)
        return (-1);
    
    gamedata->imgmini_data = mlx_get_data_addr(gamedata->imgmini,
        &gamedata->mini_bpp, &gamedata->mini_line_len, &gamedata->mini_endian);
    return (1);
}

void draw_player(char *img_data, t_camera player, unsigned int pixelsize,
                 int size_line, int bpp)
{
    int px = (int)(player.position.x * pixelsize);
    int py = (int)(player.position.y * pixelsize);
    unsigned int x, y;

    // Draw small square for player (3x3 pixels)
    for (y = 0; y < 3; ++y)
    {
        for (x = 0; x < 3; ++x)
        {
            int draw_x = px - 1 + x;
            int draw_y = py - 1 + y;

            if (draw_x >= 0 && draw_y >= 0) // Prevent negative coordinates
                draw_pixel(img_data, size_line, bpp,
                           (unsigned int)draw_x, (unsigned int)draw_y, WHITE);
        }
    }

    // Draw heading line
    t_motion playerpos;
    t_motion headingline;

    playerpos.x = px;
    playerpos.y = py;
    headingline = rotate_vector(player.vector, player.degree);
    headingline.x *= 10;
    headingline.y *= 10;

    plot_line(vec_to_coor(playerpos),
              vec_to_coor(add_vectors(playerpos, headingline)),
              img_data, size_line, bpp, WHITE);
}


static void draw_wall(char *img_data, unsigned int x, unsigned int y,
                      unsigned int pixelsize, int size_line, int bpp)
{
    unsigned int wall_x;
    unsigned int wall_y;

    wall_x = x;
    while (wall_x < x + pixelsize - 1)
    {
        wall_y = y;
        while (wall_y < y + pixelsize - 1)
        {
            draw_pixel(img_data, size_line, bpp, wall_x, wall_y, WHITE);
            ++wall_y;
        }
        ++wall_x;
    }
}

static void draw_floor(char *img_data, unsigned int x, unsigned int y,
                       unsigned int pixelsize, int size_line, int bpp)
{
    unsigned int floor_x;
    unsigned int floor_y;

    floor_x = x;
    while (floor_x < x + pixelsize)
    {
        floor_y = y;
        while (floor_y < y + pixelsize)
        {
            draw_pixel(img_data, size_line, bpp, floor_x, floor_y, GREY);
            ++floor_y;
        }
        ++floor_x;
    }
}

void draw_map(t_info *data)
{
    unsigned int pixelsize;
    unsigned int y;
    unsigned int x;

    pixelsize = data->mini_pixelsize;
    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            if (data->map[y][x] == '1')
                draw_wall(data->imgmini_data, x * pixelsize, y * pixelsize,
                    pixelsize, data->mini_line_len, data->mini_bpp);
            else
                draw_floor(data->imgmini_data, x * pixelsize, y * pixelsize,
                    pixelsize, data->mini_line_len, data->mini_bpp);
            ++x;
        }
        ++y;
    }
}