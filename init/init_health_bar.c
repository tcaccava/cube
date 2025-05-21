#include "cube3d.h"

void init_health_bar(t_game *game)
{
    game->health_bar.x = 50;
    game->health_bar.y = 50;
    game->health_bar.width = 500;
    game->health_bar.height = 40;
    game->health_bar.border = 5;
    
    game->health_bar.border_color = 0x000000;
    game->health_bar.empty_color = 0x555555;
    game->health_bar.health_color = 0xFF0000;
}
