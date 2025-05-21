/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:23:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/21 22:25:58 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


void calculate_shoot(t_game *game)
{
    double impact_x;
    double impact_y;
    int map_x;
    int map_y;
    
    int center_ray_index = DISPLAY_WIDTH / 2;
    t_ray *center_ray = &game->rays[center_ray_index];
    
    if (game->current_weapon == PORTALGUN)
    {
        if (center_ray->hit_type == '1')
        {
            impact_x = center_ray->wall_hit_x;
            impact_y = center_ray->wall_hit_y;
            map_x = (int)(impact_x / TILE_SIZE);
            map_y = (int)(impact_y / TILE_SIZE);
            if (game->portal_count < 2)
            {
                game->map.matrix[map_y][map_x] = 'P';
                game->portal_count++;
                printf("Portal added. New count: %d\n", game->portal_count);
            }
            else
            {
                remove_all_portals(game);
                game->map.matrix[map_y][map_x] = 'P';
                game->portal_count = 1;
                printf("All portals removed and new one added. Count: %d\n", game->portal_count);
            }
        }
    }
    else if (game->current_weapon == RAYGUN)
    {
        if (center_ray->hit_type == '1')
        {
            impact_x = center_ray->wall_hit_x;
            impact_y = center_ray->wall_hit_y;
            map_x = (int)(impact_x / TILE_SIZE);
            map_y = (int)(impact_y / TILE_SIZE);
            game->map.matrix[map_y][map_x] = 'i';
            damage_enemy_at_position(game, impact_x / TILE_SIZE, impact_y / TILE_SIZE, 25);
        }
        else if (center_ray->hit_type == 'D')
        {
            impact_x = center_ray->wall_hit_x;
            impact_y = center_ray->wall_hit_y;
            map_x = (int)(impact_x / TILE_SIZE);
            map_y = (int)(impact_y / TILE_SIZE);
            game->map.matrix[map_y][map_x] = 'd';
            damage_enemy_at_position(game, impact_x / TILE_SIZE, impact_y / TILE_SIZE, 25);
        }
    }
}

int mouse_button(int button, int x, int y, t_game *game)
{
    (void)x;
    (void)y;
    if (button == 1)
    {
        if (game->current_weapon == RAYGUN)
        {
            if (!game->player.weapon.is_firing)
            {
                game->player.weapon.is_firing = 1;
                game->player.weapon.current_state = WEAPON_PREFIRE;
                game->player.weapon.frame = 1;
                game->player.weapon.frame_delay = 10;
                calculate_shoot(game);
            }
        }
        else if (game->current_weapon == PORTALGUN)
        {
            if (game->portal_count < 2)
            {
                calculate_shoot(game);
            }
        }
    }
    else if (button == 4 || button == 5)
    {
        if (game->current_weapon == RAYGUN)
            game->current_weapon = PORTALGUN;
        else if (game->current_weapon == PORTALGUN)
            game->current_weapon = RAYGUN;
    }
    else if (button == 3 && game->current_weapon == PORTALGUN)
    {
        remove_all_portals(game);
    }

    return (0);
}
