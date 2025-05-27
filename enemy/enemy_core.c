/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:39:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:21:17 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static double	get_delta_angle(t_enemy *enemy, t_player *player)
{
	t_vec	dir;
	double	angle_to_player;

	dir.x = player->x - enemy->x;
	dir.y = player->y - enemy->y;
	angle_to_player = atan2(dir.y, dir.x);
	return (normalize_angle(angle_to_player - enemy->angle));
}

int	enemy_sees_you(t_enemy *enemy, t_player *player, t_map *map)
{
	t_los_args	args;
	double		delta_angle;

	delta_angle = get_delta_angle(enemy, player);
	if (fabs(delta_angle) < (M_PI / 2))
	{
		args.ex = enemy->x;
		args.ey = enemy->y;
		args.px = player->x;
		args.py = player->y;
		if (line_of_sight(args, map))
			return (1);
	}
	return (0);
}

static int	check_collision(t_map *map, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (1);
	if (map->matrix[map_y][map_x] == '1')
		return (1);
	return (0);
}

static int	is_path_blocked(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	return (check_collision(map, map_x, map_y));
}

int	line_of_sight(t_los_args pos, t_map *map)
{
	t_vec	dir;
	t_vec	curr;
	double	dist;
	double	traveled;

	dir.x = pos.px - pos.ex;
	dir.y = pos.py - pos.ey;
	dist = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x = dir.x / dist * 5.0;
	dir.y = dir.y / dist * 5.0;
	curr.x = pos.ex;
	curr.y = pos.ey;
	traveled = 0.0;
	while (traveled < dist)
	{
		if (is_path_blocked(map, curr.x, curr.y))
			return (0);
		curr.x += dir.x;
		curr.y += dir.y;
		traveled += 5.0;
	}
	return (1);
}
