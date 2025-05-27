/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:15 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 21:53:31 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	normalize_player_angle(t_player *player)
{
	while (player->angle < 0)
		player->angle += 2 * M_PI;
	while (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
}

static void	move_forward_backward(t_player *player, float speed)
{
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->x + player->dir_x * speed;
		new_y = player->y + player->dir_y * speed;
		if (player->game && is_not_wall(&player->game->map, new_x, player->y))
			player->x = new_x;
		if (player->game && is_not_wall(&player->game->map, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_down)
	{
		new_x = player->x - player->dir_x * speed;
		new_y = player->y - player->dir_y * speed;
		if (player->game && is_not_wall(&player->game->map, new_x, player->y))
			player->x = new_x;
		if (player->game && is_not_wall(&player->game->map, player->x, new_y))
			player->y = new_y;
	}
}

static void	move_strafe(t_player *player, float speed)
{
	float	strafe_angle;
	float	new_x;
	float	new_y;

	if (player->key_left)
	{
		strafe_angle = player->angle - M_PI / 2;
		new_x = player->x + cos(strafe_angle) * speed;
		new_y = player->y + sin(strafe_angle) * speed;
		if (player->game && is_not_wall(&player->game->map, new_x, player->y))
			player->x = new_x;
		if (player->game && is_not_wall(&player->game->map, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_right)
	{
		strafe_angle = player->angle + M_PI / 2;
		new_x = player->x + cos(strafe_angle) * speed;
		new_y = player->y + sin(strafe_angle) * speed;
		if (player->game && is_not_wall(&player->game->map, new_x, player->y))
			player->x = new_x;
		if (player->game && is_not_wall(&player->game->map, player->x, new_y))
			player->y = new_y;
	}
}

void	move_player(t_player *player)
{
	float	angle_speed;
	float	speed;

	angle_speed = 0.05;
	speed = 10.0;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->turn_back)
		player->angle += M_PI;
	normalize_player_angle(player);
	update_camera_vectors(player);
	move_forward_backward(player, speed);
	move_strafe(player, speed);
}
