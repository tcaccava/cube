/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:19:58 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:59 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	rotate_left(t_player *player, float angle_speed)
{
	player->angle -= angle_speed;
	normalize_player_angle(player);
	update_camera_vectors(player);
}

void	rotate_right(t_player *player, float angle_speed)
{
	player->angle += angle_speed;
	normalize_player_angle(player);
	update_camera_vectors(player);
}

void	turn_around(t_player *player)
{
	player->angle += M_PI;
	normalize_player_angle(player);
	update_camera_vectors(player);
}

void	normalize_player_angle(t_player *player)
{
	while (player->angle < 0)
		player->angle += 2 * M_PI;
	while (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
}

void	process_movement_keys(t_player *player)
{
	float	speed;

	speed = 10.0;
	if (player->key_up)
		move_forward(player, speed);
	if (player->key_down)
		move_backward(player, speed);
	if (player->key_left)
		move_strafe_left(player, speed);
	if (player->key_right)
		move_strafe_right(player, speed);
}
