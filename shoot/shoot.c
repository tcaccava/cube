/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:23:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 18:13:12 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	handle_portal_placement(t_game *game, t_ray *center_ray)
{
	double	impact_x;
	double	impact_y;
	int		map_x;
	int		map_y;

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
		printf("All portals removed and new one added. Count: %d\n",
			game->portal_count);
	}
}

static double	calculate_distance_from_line(double dx, double dy,
		double ray_dir_x, double ray_dir_y)
{
	double	cross_product;
	double	distance_from_line;

	cross_product = fabs(dx * ray_dir_y - dy * ray_dir_x);
	distance_from_line = cross_product / sqrt(ray_dir_x * ray_dir_x + ray_dir_y
			* ray_dir_y);
	return (distance_from_line);
}

int	check_enemy_hit(t_game *game, int i, double ray_dir_x, double ray_dir_y)
{
	t_enemy	*enemy;
	double	dx_to_enemy;
	double	dy_to_enemy;
	double	dis_to_ene;
	double	dot_product;

	enemy = &game->enemies[i];
	dx_to_enemy = enemy->x - game->player.x;
	dy_to_enemy = enemy->y - game->player.y;
	dis_to_ene = sqrt(dx_to_enemy * dx_to_enemy + dy_to_enemy * dy_to_enemy);
	dot_product = (dx_to_enemy * ray_dir_x + dy_to_enemy * ray_dir_y)
		/ dis_to_ene;
	if (dot_product > 0.9 && dis_to_ene < game->rays[DISPLAY_WIDTH
			/ 2].distance)
	{
		if (calculate_distance_from_line(dx_to_enemy, dy_to_enemy, ray_dir_x,
				ray_dir_y) < TILE_SIZE * 0.4)
			return (1);
	}
	return (0);
}

void	damage_hit_enemy(t_game *game, int enemy_index)
{
	t_enemy	*enemy;
	int		map_x;
	int		map_y;

	enemy = &game->enemies[enemy_index];
	map_x = (int)(enemy->x / TILE_SIZE);
	map_y = (int)(enemy->y / TILE_SIZE);
	printf("Enemy hit at [%d, %d]\n", map_x, map_y);
	if (damage_enemy_at_position(game, map_x, map_y, 100))
	{
		printf("Enemy flatlined at [%d, %d]\n", map_x, map_y);
	}
}
