/* ************************************************************************** */
/*                                                                            */
/*   minimap.c - Gestion complète de la mini-carte                          */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void init_minimap(t_game *game)
{
    game->minimap.size = 150;
    game->minimap.x = 20;
    game->minimap.y = DISPLAY_HEIGHT - game->minimap.size - 20;
    game->minimap.cell_size = 10;
    game->minimap.border = 2;
    game->minimap.visible_radius = (game->minimap.size - 2 * game->minimap.border) / (2 * game->minimap.cell_size);
    game->minimap.show = 1;
    
    game->minimap.border_color = 0xFFFFFF;
    game->minimap.bg_color = 0x000000;
    game->minimap.wall_color = 0x888888;
    game->minimap.door_color = 0x8B4513;
    game->minimap.portal_color = 0x00FFFF;
    game->minimap.player_color = 0xFF0000;
}

void draw_minimap_background(t_game *game)
{
    t_minimap *mini_map = &game->minimap;
    char *pixel;
    int x, y;

    y = mini_map->y;
    while (y < mini_map->y + mini_map->size)
    {
        x = mini_map->x;
        while (x < mini_map->x + mini_map->size)
        {
            if (x < mini_map->x + mini_map->border || x >= mini_map->x + mini_map->size - mini_map->border || 
                y < mini_map->y + mini_map->border || y >= mini_map->y + mini_map->size - mini_map->border)
            {
                pixel = game->screen.addr + (y * game->screen.line_length + x * (game->screen.bits_per_pixel / 8));
                *(unsigned int *)pixel = mini_map->border_color;
            }
            else
            {
                pixel = game->screen.addr + (y * game->screen.line_length + x * (game->screen.bits_per_pixel / 8));
                *(unsigned int *)pixel = mini_map->bg_color;
            }
            x++;
        }
        y++;
    }
}

void draw_minimap_cell(t_game *game, int map_x, int map_y, int screen_x, int screen_y)
{
    t_minimap *mini_map = &game->minimap;
    char *pixel;
    char cell_type;
    unsigned int cell_color;
    int row, col, screen_pixel_x, screen_pixel_y;

    if (map_x >= 0 && map_x < game->map.width && map_y >= 0 && map_y < game->map.height)
    {
        cell_type = game->map.matrix[map_y][map_x];
        if (cell_type == '1')
            cell_color = mini_map->wall_color;
        else if (cell_type == 'D')
            cell_color = mini_map->door_color;
        else if (cell_type == 'P')
            cell_color = mini_map->portal_color;
        else
            cell_color = mini_map->bg_color;
            
        row = 0;
        while (row < mini_map->cell_size)
        {
            col = 0;
            while (col < mini_map->cell_size)
            {
                screen_pixel_x = screen_x + col;
                screen_pixel_y = screen_y + row;
                if (screen_pixel_x >= mini_map->x + mini_map->border && 
                    screen_pixel_x < mini_map->x + mini_map->size - mini_map->border && 
                    screen_pixel_y >= mini_map->y + mini_map->border && 
                    screen_pixel_y < mini_map->y + mini_map->size - mini_map->border)
                {
                    pixel = game->screen.addr + (screen_pixel_y * game->screen.line_length + 
                            screen_pixel_x * (game->screen.bits_per_pixel / 8));
                    *(unsigned int *)pixel = cell_color;
                }
                col++;
            }
            row++;
        }
    }
}

void draw_minimap_cells(t_game *game)
{
    t_minimap *mini_map = &game->minimap;
    int center_x = mini_map->x + mini_map->size / 2;
    int center_y = mini_map->y + mini_map->size / 2;
    int player_map_x = (int)(game->player.x / TILE_SIZE);
    int player_map_y = (int)(game->player.y / TILE_SIZE);
    int row, col, map_x, map_y, cell_x, cell_y;

    row = -mini_map->visible_radius;
    while (row <= mini_map->visible_radius)
    {
        col = -mini_map->visible_radius;
        while (col <= mini_map->visible_radius)
        {
            map_x = player_map_x + col;
            map_y = player_map_y + row;
            cell_x = center_x + col * mini_map->cell_size;
            cell_y = center_y + row * mini_map->cell_size;
            draw_minimap_cell(game, map_x, map_y, cell_x, cell_y);
            col++;
        }
        row++;
    }
}

void minimap(t_game *game)
{
    if (!game->minimap.show)
        return;
    draw_minimap_background(game);
    draw_minimap_cells(game);
    draw_minimap_player(game);
}