/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:26 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:17:27 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	check_enemy_line_distance(t_shoot_params *params)
{
	double	dx_to_enemy;
	double	dy_to_enemy;
	double	distance_to_enemy;
	double	dot_product;

	dx_to_enemy = params->enemy->x - params->player_x;
	dy_to_enemy = params->enemy->y - params->player_y;
	distance_to_enemy = sqrt(dx_to_enemy * dx_to_enemy + dy_to_enemy
			* dy_to_enemy);
	dot_product = (dx_to_enemy * params->ray_dir_x + dy_to_enemy
			* params->ray_dir_y) / distance_to_enemy;
	if (dot_product <= 0.9 || distance_to_enemy >= params->center_ray->distance)
		return (0);
	return (1);
}

int	is_enemy_in_line_of_fire(t_game *game, t_shoot_params *params)
{
	double	dx_to_enemy;
	double	dy_to_enemy;
	double	cross_product;
	double	distance_from_line;

	(void)game;
	if (!params->enemy->active || params->enemy->state == DEAD)
		return (0);
	if (!check_enemy_line_distance(params))
		return (0);
	dx_to_enemy = params->enemy->x - params->player_x;
	dy_to_enemy = params->enemy->y - params->player_y;
	cross_product = fabs(dx_to_enemy * params->ray_dir_y - dy_to_enemy
			* params->ray_dir_x);
	distance_from_line = cross_product / sqrt(params->ray_dir_x
			* params->ray_dir_x + params->ray_dir_y * params->ray_dir_y);
	return (distance_from_line < TILE_SIZE * 0.4);
}

int	damage_enemy(t_enemy *enemy, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(enemy->x / TILE_SIZE);
	map_y = (int)(enemy->y / TILE_SIZE);
	printf("Enemy hit at [%d, %d]\n", map_x, map_y);
	if (damage_enemy_at_position(game, map_x, map_y, 100))
	{
		printf("Enemy flatlined at [%d, %d]\n", map_x, map_y);
		return (1);
	}
	return (1);
}

void	apply_wall_damage(t_game *game, t_ray *center_ray)
{
	double	impact_x;
	double	impact_y;
	int		map_x;
	int		map_y;

	impact_x = center_ray->wall_hit_x;
	impact_y = center_ray->wall_hit_y;
	map_x = (int)(impact_x / TILE_SIZE);
	map_y = (int)(impact_y / TILE_SIZE);
	apply_damage_to_surface(game, center_ray->hit_type, map_x, map_y);
}

void	apply_damage_to_surface(t_game *game, char hit_type,
		int map_x, int map_y)
{
	if (hit_type == '1')
		game->map.matrix[map_y][map_x] = 'i';
	else if (hit_type == 'D')
		game->map.matrix[map_y][map_x] = 'd';
	else if (hit_type == 'd')
		game->map.matrix[map_y][map_x] = 'o';
}
