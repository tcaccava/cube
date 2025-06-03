/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_core_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:17 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:18 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_los_data(t_los_data *d, t_point enemy_pos,
		t_point player_pos)
{
	double	dx;
	double	dy;

	dx = player_pos.x - enemy_pos.x;
	dy = player_pos.y - enemy_pos.y;
	d->distance = sqrt(dx * dx + dy * dy);
	d->step_x = (dx / d->distance) * 5.0;
	d->step_y = (dy / d->distance) * 5.0;
	d->x = enemy_pos.x;
	d->y = enemy_pos.y;
	d->traveled = 0.0;
}

static int	check_wall_hit(t_los_data *d, t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = (int)(d->x / TILE_SIZE);
	map_y = (int)(d->y / TILE_SIZE);
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (1);
	return (map->matrix[map_y][map_x] == '1');
}

int	line_of_sight(t_point enemy_pos, t_point player_pos, t_map *map)
{
	t_los_data	d;

	init_los_data(&d, enemy_pos, player_pos);
	while (d.traveled < d.distance)
	{
		if (check_wall_hit(&d, map))
			return (0);
		d.x += d.step_x;
		d.y += d.step_y;
		d.traveled += 5.0;
	}
	return (1);
}

static void	handle_enemy_death(t_enemy *enemy)
{
	enemy->death_timer = 300;
	enemy->animation.current_frame = 0;
	enemy->animation.frame_counter = 0;
	enemy->state = DEAD;
}

int	damage_enemy_at_position(t_game *game, int tile_x, int tile_y, int damage)
{
	int			i;
	t_enemy		*enemy;
	int			enemy_tile_x;
	int			enemy_tile_y;

	i = 0;
	while (i < game->num_enemies)
	{
		enemy = &game->enemies[i];
		enemy_tile_x = (int)(enemy->x / TILE_SIZE);
		enemy_tile_y = (int)(enemy->y / TILE_SIZE);
		if (enemy_tile_x == tile_x && enemy_tile_y == tile_y && enemy->active)
		{
			enemy->health -= damage;
			if (enemy->health <= 0)
			{
				handle_enemy_death(enemy);
				return (1);
			}
			return (0);
		}
		i++;
	}
	return (0);
}
