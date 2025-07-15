#include "../includes/struct.h"

void plot_line(t_coordinates po, t_coordinates po1, char *image, int leng, int bpp, unsigned int colour)
{
    if (abs_int(po1.y - po.y) < abs_int(po1.x - po.x))
    {
        if (po.x > po1.x)
            plot_line_horizontal(po1, po, image, leng, bpp, colour);
        else
            plot_line_horizontal(po, po1, image, leng, bpp, colour);
    }
    else
    {
        if (po.y > po1.y)
            plot_line_vertical(po1, po, image, leng, bpp, colour);
        else
            plot_line_vertical(po, po1, image, leng, bpp, colour);
    }
}

void plot_line_horizontal(t_coordinates po, t_coordinates po1, char *image, int leng, int bpp, unsigned int colour)
{
    int dx;
    int dy;
    int yi;
    int difference;

    dx = po1.x - po.x;
    dy = po1.y - po.y;
    yi = 1;
    if (dy < 0)
        yi = -1;
    if (dy < 0)
        dy = -dy;
    difference = (2 * dy) - dx;
    while (po.x <= po1.x)
    {
        draw_pixel(image, leng, bpp, po.x, po.y, colour);
        if (difference > 0)
        {
            po.y = po.y + yi;
            difference = difference + (2 * (dy - dx));
        }
        else
            difference = difference + (2 * dy);
        po.x = po.x + 1;
    }
}

void plot_line_vertical(t_coordinates po, t_coordinates po1, char *image, int leng, int bpp, unsigned int colour)
{
    int dy;
    int dx;
    int xi;
    int difference;

    dy = po1.y - po.y;
    dx = po1.x - po.x;
    xi = 1;
    if (dx < 0)
        xi = -1;
    if (dx < 0)
        dx = -dx;
    difference = (2 * dx) - dy;
    while (po.y <= po1.y)
    {
        draw_pixel(image, leng, bpp, po.x, po.y, colour);
        if (difference > 0)
        {
            po.x = po.x + xi;
            difference = difference + (2 * (dx - dy));
        }
        else
            difference = difference + (2 * dx);
        po.y = po.y + 1;
    }
}

long abs_int(int number)
{
    if (number >= 0)
        return ((long)number);
    else
        return ((long)-1 * number);
}