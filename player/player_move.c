/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:16 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:17 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	move_player(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.05;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->turn_back)
		player->angle += M_PI;
	while (player->angle < 0)
		player->angle += 2 * M_PI;
	while (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
	update_camera_vectors(player);
	if (player->key_up)
		move_forward(player, player->move_speed);
	if (player->key_down)
		move_backward(player, player->move_speed);
	if (player->key_left)
		move_strafe_left(player, player->move_speed);
	if (player->key_right)
		move_strafe_right(player, player->move_speed);
	check_portal_teleportation(player->game);
	check_weapon_pickup(player);
}
