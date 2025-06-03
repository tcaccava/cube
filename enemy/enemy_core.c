/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:19 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:20 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	update_enemy(t_enemy *enemy, t_player *player, t_map *map)
{
	if (enemy->health <= 0)
	{
		enemy->state = DEAD;
		return ;
	}
	if (enemy->state == IDLE)
		idle(enemy, player, map);
	else if (enemy->state == SEARCH)
		search(enemy, player, map);
	else if (enemy->state == SHOOT)
		shoot(enemy, player, map);
	else if (enemy->state == MELEE)
		melee(enemy, player, map);
}

int	enemy_sees_you(t_enemy *enemy, t_player *player, t_map *map)
{
	double	dx;
	double	dy;
	double	angle_to_player;
	double	delta_angle;
	double	fov;

	dx = player->x - enemy->x;
	dy = player->y - enemy->y;
	angle_to_player = atan2(dy, dx);
	delta_angle = normalize_angle(angle_to_player - enemy->angle);
	fov = M_PI;
	if (fabs(delta_angle) < fov / 2)
	{
		if (line_of_sight((t_point){enemy->x, enemy->y},
			(t_point){player->x, player->y}, map))
			return (1);
	}
	return (0);
}

void	update_camera_vectors(t_player *player)
{
	double	fov_half;

	fov_half = player->fov / 2.0;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * tan(fov_half);
	player->plane_y = cos(player->angle) * tan(fov_half);
}
