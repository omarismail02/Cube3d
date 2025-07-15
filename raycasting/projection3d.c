#include "../includes/struct.h"

static void draw_floor_ceiling(t_info *data, unsigned int top,
    unsigned int bottom, unsigned int x)
{
    t_coordinates ceilingtop = {x, 0};
    t_coordinates ceilingbottom = {x, top - 1};
    t_coordinates floortop = {x, bottom + 1};
    t_coordinates floorbottom = {x, data->img_height - 1};

    plot_line(ceilingtop, ceilingbottom, data->img_data, data->line_len, data->bpp, data->ceiling_colour);
    plot_line(floortop, floorbottom, data->img_data, data->line_len, data->bpp, data->floor_colour);
}

static unsigned int get_texture_colour(t_info *data, unsigned int tex_index, unsigned int x, unsigned int y)
{
    if (x >= (unsigned int)data->tex_width[tex_index] || y >= (unsigned int)data->tex_height[tex_index])
        return 0x00000000;
        
    unsigned int offset = y * data->texture_line_len[tex_index] + x * (data->texture_bpp[tex_index] / 8);
    unsigned char *dst = (unsigned char *)data->texture_data[tex_index] + offset;
    return *(unsigned int *)dst;
}

static void draw_tex_wall_column(t_info *data, unsigned int x, t_dda *result,
    t_info *vars)
{
    unsigned int y = 0;
    while (y <= vars->bottom - vars->top)
    {
        unsigned int colour;
        if (result->dir == EAST || result->dir == NORTH)
            colour = get_texture_colour(data, result->dir,
                (unsigned int)((1.0 - result->position) * data->tex_width[result->dir]),
                (unsigned int)(vars->tex_start + y * vars->step));
        else
            colour = get_texture_colour(data, result->dir,
                (unsigned int)(result->position * data->tex_width[result->dir]),
                (unsigned int)(vars->tex_start + y * vars->step));

        colour = adjust_brightness(colour, vars->wall_height_perc);
        draw_pixel(data->img_data, data->line_len, data->bpp, x, y + vars->top, colour);
        y++;
    }
}

static void draw_tex_wall(t_info *data, unsigned int x, unsigned int wall_height,
    t_dda *result)
{
    t_info vars;

    vars.wall = data->texture[result->dir];
    vars.step = 1.0 * data->tex_height[result->dir] / wall_height;
    if (wall_height > data->img_height)
    {
        vars.top = 0;
        vars.bottom = data->img_height - 1;
        vars.tex_start = (((1 - (1.0 * data->img_height / wall_height)) / 2.0)
                * data->tex_height[result->dir]);
    }
    else
    {
        vars.top = (data->img_height - wall_height) / 2;
        vars.bottom = (data->img_height + wall_height) / 2;
        vars.tex_start = 0.0;
    }
    vars.wall_height_perc = 1.0 * wall_height / data->img_height;
    draw_tex_wall_column(data, x, result, &vars);
    draw_floor_ceiling(data, vars.top, vars.bottom, x);
}

void create_projection(t_info *data)
{
    unsigned int x;
    double angle;
    double ps;
    unsigned int wall_height;
    t_dda dda_result;

    x = 0;
    while (x < data->img_width)
    {
        ps = tanf(((data->player.fov / 2.0) / 180) * M_PI);
        angle = (atanf(-ps + ((2.0 * ps * x) / data->img_width)) * 180) / M_PI;
        dda_result = apply_dda(data->player.position,
                rotate_vector(data->player.vector,
                    data->player.degree - angle), angle, data->map);
        wall_height = (unsigned int)(data->img_height / dda_result.view_dist);
        draw_tex_wall(data, x, wall_height, &dda_result);
        x++;
    }
}