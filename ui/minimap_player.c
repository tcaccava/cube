/* ************************************************************************** */
/*                                                                            */
/*   minimap_player.c - Rendu du joueur sur la mini-carte                   */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void draw_minimap_cone(t_game *game)
{
    t_minimap *mini_map = &game->minimap;
    char *pixel;
    int center_x = mini_map->x + mini_map->size / 2;
    int center_y = mini_map->y + mini_map->size / 2;
    double fov = M_PI / 2;
    double start_angle = game->player.angle - fov / 2;
    double end_angle = game->player.angle + fov / 2;
    double step = 0.01;
    double angle;
    int i, x, y;

    angle = start_angle;
    while (angle <= end_angle)
    {
        i = 0;
        while (i < 45)
        {
            x = center_x + cos(angle) * i;
            y = center_y + sin(angle) * i;
            if (x >= mini_map->x + mini_map->border && x < mini_map->x + mini_map->size - mini_map->border && 
                y >= mini_map->y + mini_map->border && y < mini_map->y + mini_map->size - mini_map->border)
            {
                pixel = game->screen.addr + (y * game->screen.line_length + x * (game->screen.bits_per_pixel / 8));
                *(unsigned int *)pixel = mini_map->player_color;
            }
            i++;
        }
        angle += step;
    }
}

void draw_player_circle(t_game *game, int center_x, int center_y)
{
    t_minimap *mini_map = &game->minimap;
    char *pixel;
    int player_size = 4;
    int px, py, x, y;

    py = -player_size;
    while (py <= player_size)
    {
        px = -player_size;
        while (px <= player_size)
        {
            if (px * px + py * py <= player_size * player_size)
            {
                x = center_x + px;
                y = center_y + py;
                if (x >= mini_map->x + mini_map->border && x < mini_map->x + mini_map->size - mini_map->border && 
                    y >= mini_map->y + mini_map->border && y < mini_map->y + mini_map->size - mini_map->border)
                {
                    pixel = game->screen.addr + (y * game->screen.line_length + x * (game->screen.bits_per_pixel / 8));
                    *(unsigned int *)pixel = mini_map->player_color;
                }
            }
            px++;
        }
        py++;
    }
}

void draw_minimap_player(t_game *game)
{
    t_minimap *mini_map = &game->minimap;
    int center_x = mini_map->x + mini_map->size / 2;
    int center_y = mini_map->y + mini_map->size / 2;

    draw_player_circle(game, center_x, center_y);
    draw_minimap_cone(game);
}