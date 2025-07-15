#include "../includes/struct.h"

t_motion calc_ray_vector(double degree, double distance)
{
    t_motion ray;
    double radians;

    radians = (degree / 180.0) * M_PI;
    ray.x = cos(radians) * distance;
    ray.y = sin(radians) * distance;
    return (ray);
}

void draw_viewing_cone(t_info *data)
{
    double i;
    t_dda result;
    t_motion current_heading;
    t_motion ray;

    i = (-1 * (data->player.fov / 2.0));
    while (i < (data->player.fov / 2.0))
    {
        current_heading = rotate_vector(data->player.vector, data->player.degree + i);
        result = apply_dda(data->player.position, current_heading, i, data->map);
        ray = calc_ray_vector(data->player.degree + i, result.range);
        draw_ray(data->imgmini_data, ray, data->player.position,
                 data->mini_pixelsize, data->mini_line_len, data->mini_bpp);
        i += 0.1;
    }
}

void draw_ray(char *img_data, t_motion ray, t_motion playerpos,
              unsigned int pixelsize, int size_line, int bpp)
{
    t_coordinates start;
    t_coordinates end;

    start.x = (int)(playerpos.x * pixelsize);
    start.y = (int)(playerpos.y * pixelsize);
    end.x = start.x + (int)(ray.x * pixelsize);
    end.y = start.y - (int)(ray.y * pixelsize);
    plot_line(start, end, img_data, size_line, bpp, RED);
}