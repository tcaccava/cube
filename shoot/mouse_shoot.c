/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_shoot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:02:41 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 18:14:12 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	calculate_shoot(t_game *game)
{
	int		center_ray_index;
	t_ray	*center_ray;
	double	ray_dir_x;
	double	ray_dir_y;

	center_ray_index = DISPLAY_WIDTH / 2;
	center_ray = &game->rays[center_ray_index];
	if (game->current_weapon == PORTALGUN)
	{
		if (center_ray->hit_type == '1')
		{
			handle_portal_placement(game, center_ray);
		}
	}
	else if (game->current_weapon == RAYGUN)
	{
		ray_dir_x = cos(game->player.angle);
		ray_dir_y = sin(game->player.angle);
		if (!handle_raygun_enemies(game, ray_dir_x, ray_dir_y))
		{
			handle_raygun_walls(game, center_ray);
		}
	}
}

void	handle_left_click(t_game *game)
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

int	mouse_button(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (game->map.north.ptr != NULL)
		return (0);
	if (button == 1)
	{
		handle_left_click(game);
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

int	handle_raygun_enemies(t_game *game, double ray_dir_x, double ray_dir_y)
{
	int		i;
	t_enemy	*enemy;
	double	closest_enemy_distance;
	int		enemy_hit;

	i = 0;
	enemy_hit = 0;
	closest_enemy_distance = game->rays[DISPLAY_WIDTH / 2].distance;
	(void)closest_enemy_distance;
	while (i < game->num_enemies)
	{
		enemy = &game->enemies[i];
		if (enemy->active && enemy->state != DEAD)
		{
			if (check_enemy_hit(game, i, ray_dir_x, ray_dir_y))
			{
				damage_hit_enemy(game, i);
				enemy_hit = 1;
				break ;
			}
		}
		i++;
	}
	return (enemy_hit);
}

void	handle_raygun_walls(t_game *game, t_ray *center_ray)
{
	int		map_x;
	int		map_y;
	double	impact_x;
	double	impact_y;

	impact_x = center_ray->wall_hit_x;
	impact_y = center_ray->wall_hit_y;
	map_x = (int)(impact_x / TILE_SIZE);
	map_y = (int)(impact_y / TILE_SIZE);
	if (center_ray->hit_type == '1')
	{
		game->map.matrix[map_y][map_x] = 'i';
	}
	else if (center_ray->hit_type == 'D')
	{
		game->map.matrix[map_y][map_x] = 'd';
	}
}
