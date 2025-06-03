/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:19:56 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:57 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	move_forward(t_player *player, float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->x + cos(player->angle) * speed;
	new_y = player->y + sin(player->angle) * speed;
	if (player->game && is_not_wall_for_movement(&player->game->map,
			new_x, player->y))
		player->x = new_x;
	if (player->game && is_not_wall_for_movement(&player->game->map,
			player->x, new_y))
		player->y = new_y;
}

void	move_backward(t_player *player, float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->x - cos(player->angle) * speed;
	new_y = player->y - sin(player->angle) * speed;
	if (player->game && is_not_wall(&player->game->map, new_x, player->y))
		player->x = new_x;
	if (player->game && is_not_wall(&player->game->map, player->x, new_y))
		player->y = new_y;
}

void	move_strafe_left(t_player *player, float speed)
{
	float	strafe_angle;
	float	new_x;
	float	new_y;

	strafe_angle = player->angle - M_PI / 2;
	new_x = player->x + cos(strafe_angle) * speed;
	new_y = player->y + sin(strafe_angle) * speed;
	if (player->game && is_not_wall(&player->game->map, new_x, player->y))
		player->x = new_x;
	if (player->game && is_not_wall(&player->game->map, player->x, new_y))
		player->y = new_y;
}

void	move_strafe_right(t_player *player, float speed)
{
	float	strafe_angle;
	float	new_x;
	float	new_y;

	strafe_angle = player->angle + M_PI / 2;
	new_x = player->x + cos(strafe_angle) * speed;
	new_y = player->y + sin(strafe_angle) * speed;
	if (player->game && is_not_wall(&player->game->map, new_x, player->y))
		player->x = new_x;
	if (player->game && is_not_wall(&player->game->map, player->x, new_y))
		player->y = new_y;
}
