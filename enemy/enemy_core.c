/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:39:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/22 18:26:15 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void update_enemy(t_enemy *enemy, t_player *player, t_map *map)
{
    double dx = player->x - enemy->x;
    double dy = player->y - enemy->y;
    double distance = sqrt(dx * dx + dy * dy);
    
    if (enemy->health <= 0)
    {
        enemy->state = DEAD;
        return;
    }
    
    if (enemy->state == IDLE)
        idle(enemy, player, map, dx, dy, distance);
    else if (enemy->state == SEARCH)
        search(enemy, player, map, dx, dy, distance);
    else if (enemy->state == SHOOT)
        shoot(enemy, player, map, dx, dy, distance);
    else if (enemy->state == MELEE)
        melee(enemy, player, map, dx, dy, distance);
}

int enemy_sees_you(t_enemy *enemy, t_player *player, t_map *map)
{
    double dx = player->x - enemy->x;
    double dy = player->y - enemy->y;
    double angle_to_player = atan2(dy, dx);
    double delta_angle = normalize_angle(angle_to_player - enemy->angle);
    double fov = M_PI;
    
    if (fabs(delta_angle) < fov / 2)
    {
        if (line_of_sight(enemy->x, enemy->y, player->x, player->y, map))
            return (1);
    }
    return (0);
}

int line_of_sight(double ex, double ey, double px, double py, t_map *map)
{
    double dx = px - ex;
    double dy = py - ey;
    double distance = sqrt(dx * dx + dy * dy);
    double step_x = (dx / distance) * 5.0;
    double step_y = (dy / distance) * 5.0;
    double x = ex;
    double y = ey;
    double traveled = 0.0;
    int map_x, map_y;
    
    while (traveled < distance)
    {
        map_x = (int)(x / TILE_SIZE);
        map_y = (int)(y / TILE_SIZE);
        
        if (map_x < 0 || map_x >= map->width || 
            map_y < 0 || map_y >= map->height)
            return (0);
            
        if (map->matrix[map_y][map_x] == '1')
            return (0);
            
        x += step_x;
        y += step_y;
        traveled += 5.0;
    }
    return (1);
}

int damage_enemy_at_position(t_game *game, int tile_x, int tile_y, int damage)
{
    int i = 0;
    
    while (i < game->num_enemies)
    {
        t_enemy *enemy = &game->enemies[i];
        int enemy_tile_x = (int)(enemy->x / TILE_SIZE);
        int enemy_tile_y = (int)(enemy->y / TILE_SIZE);

        if (enemy_tile_x == tile_x && enemy_tile_y == tile_y && enemy->active)
        {
            enemy->health -= damage;
            if (enemy->health <= 0)
            {
                enemy->death_timer = 300;
                enemy->animation.current_frame = 0;
                enemy->animation.frame_counter = 0;
                enemy->state = DEAD;
                return (1);
            }
            else
                return (0);
        }
        i++;
    }
    return (0);
}

void update_camera_vectors(t_player *player)
{
    double fov_half = player->fov / 2.0;

    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
    player->plane_x = -sin(player->angle) * tan(fov_half);
    player->plane_y = cos(player->angle) * tan(fov_half);
}