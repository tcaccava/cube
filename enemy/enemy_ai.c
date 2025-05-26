#include "../cube3d.h"

void idle(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
    double move_x, move_y;
    double speed = 1.5;
    int next_x, next_y;
    
    (void)dx; (void)dy; (void)d;
    
    move_x = cos(e->angle) * speed;
    move_y = sin(e->angle) * speed;
    
    next_x = (int)((e->x + move_x) / TILE_SIZE);
    next_y = (int)((e->y + move_y) / TILE_SIZE);
    
    if (next_x >= 0 && next_x < m->width && 
        next_y >= 0 && next_y < m->height &&
        m->matrix[next_y][next_x] != '1')
    {
        e->x += move_x;
        e->y += move_y;
    }
    else
    {
        e->angle += ((rand() % 60) - 30) * M_PI / 180;
        e->angle = normalize_angle(e->angle);
    }
    
    if (enemy_sees_you(e, p, m))
    {
        e->state = SEARCH;
        e->sees_player = 1;
    }
}

void search(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
    double move_x, move_y, angle_to_player;
    double speed = 3.0;
    int next_x, next_y;
    double distance_in_tiles = d / TILE_SIZE;
    
    if (!enemy_sees_you(e, p, m))
    {
        e->state = IDLE;
        e->sees_player = 0;
        return;
    }
    
    if (distance_in_tiles < 1.5)
    {
        e->state = MELEE;
        e->cooldown = 0;
        return;
    }
    
    if (distance_in_tiles < 6)
    {
        e->state = SHOOT;
        e->cooldown = 0;
        return;
    }
    
    angle_to_player = atan2(dy, dx);
    e->angle = angle_to_player;
    
    move_x = cos(e->angle) * speed;
    move_y = sin(e->angle) * speed;
    
    next_x = (int)((e->x + move_x) / TILE_SIZE);
    next_y = (int)((e->y + move_y) / TILE_SIZE);
    
    if (next_x >= 0 && next_x < m->width && 
        next_y >= 0 && next_y < m->height &&
        m->matrix[next_y][next_x] != '1')
    {
        e->x += move_x;
        e->y += move_y;
    }
}

void shoot(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
    double angle_to_player;
    double distance_in_tiles = d / TILE_SIZE;
    
    if (!enemy_sees_you(e, p, m))
    {
        e->state = SEARCH;
        e->sees_player = 0;
        return;
    }
    
    if (distance_in_tiles >= 6.0)
    {
        e->state = SEARCH;
        return;
    }
    
    if (distance_in_tiles < 1.5)
    {
        e->state = MELEE;
        e->cooldown = 0;
        return;
    }
    
    angle_to_player = atan2(dy, dx);
    e->angle = angle_to_player;
    
    if (e->cooldown <= 0)
    {
        p->health -= 10;
        e->cooldown = 180;
    }
    else
        e->cooldown--;
}

void melee(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
    double angle_to_player;
    double distance_in_tiles = d / TILE_SIZE;
    
    if (!enemy_sees_you(e, p, m) || distance_in_tiles >= 1.5)
    {
        e->state = SEARCH;
        return;
    }
    
    angle_to_player = atan2(dy, dx);
    e->angle = angle_to_player;
    
    if (e->cooldown <= 0)
    {
        p->health -= 25;
        e->cooldown = 90;
    }
    else
        e->cooldown--;
}

void update_enemy_position_on_map(t_game *game, t_enemy *enemy, double old_x, double old_y)
{
    int old_map_x = (int)(old_x);
    int old_map_y = (int)(old_y);
    int new_map_x = (int)(enemy->x);
    int new_map_y = (int)(enemy->y);
    int i;

    if (old_map_x != new_map_x || old_map_y != new_map_y)
    {
        if (old_map_x >= 0 && old_map_x < game->map.width &&
            old_map_y >= 0 && old_map_y < game->map.height)
        {
            if (game->map.matrix[old_map_y][old_map_x] == 'M')
            {
                int nemico_presente = 0;
                i = 0;
                while (i < game->num_enemies)
                {
                    if (game->enemies[i].active &&
                        (int)(game->enemies[i].x) == old_map_x &&
                        (int)(game->enemies[i].y) == old_map_y)
                    {
                        nemico_presente = 1;
                        break;
                    }
                    i++;
                }
                if (!nemico_presente)
                    game->map.matrix[old_map_y][old_map_x] = '0';
            }
        }

        if (new_map_x >= 0 && new_map_x < game->map.width &&
            new_map_y >= 0 && new_map_y < game->map.height && enemy->active)
        {
            game->map.matrix[new_map_y][new_map_x] = 'M';
        }
    }
}