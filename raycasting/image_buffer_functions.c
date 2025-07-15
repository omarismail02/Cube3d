#include "../includes/struct.h"
#include <string.h> // for memset

void draw_pixel(char *img_data, int size_line, int bpp,
                unsigned int x, unsigned int y, unsigned int colour)
{
    unsigned char *dst;

    if (!img_data)
        return;

    // Assuming a max resolution; alternatively, pass width/height
    if (x >= 1920 || y >= 1080) // Change if your window is smaller
        return;

    dst = (unsigned char *)img_data + y * size_line + x * (bpp / 8);

    if (bpp == 32)
        *(unsigned int *)dst = colour;
    else if (bpp == 24)
    {
        dst[0] = colour & 0xFF;
        dst[1] = (colour >> 8) & 0xFF;
        dst[2] = (colour >> 16) & 0xFF;
    }
}

void clear_image(char *img_data, int width, int height, int size_line, int bpp)
{
    (void)width;  // Mark as intentionally unused
    (void)bpp;    // Mark as intentionally unused
    
    if (!img_data)
        return;

    // Clear the whole image buffer (fill with zeros = black & transparent)
    // We clear size_line bytes for each line, for all height lines
    for (int y = 0; y < height; y++)
        memset(img_data + y * size_line, 0, size_line);
}