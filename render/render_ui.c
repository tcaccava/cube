#include "../cube3d.h"

void draw_crosshair(t_game *game)
{
    int center_x = DISPLAY_WIDTH / 2;
    int center_y = DISPLAY_HEIGHT / 2;
    int size = 5; // size of crosshair
    unsigned int color = 0x000000;
    int i = -size;
    char *pixel = NULL;
    while (i <= size)
    {
        if (center_y + i >= 0 && center_y + i < DISPLAY_HEIGHT)
        {
            pixel = game->screen.addr + ((center_y + i) * game->screen.line_length + 
                         center_x * (game->screen.bits_per_pixel / 8));
            *(unsigned int*)pixel = color;
        }
        if (center_x + i >= 0 && center_x + i < DISPLAY_WIDTH)
        {
            pixel = game->screen.addr + (center_y * game->screen.line_length + 
                         (center_x + i) * (game->screen.bits_per_pixel / 8));
            *(unsigned int*)pixel = color;
        }
        i++;
    }
}
