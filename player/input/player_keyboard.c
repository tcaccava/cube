/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:19:48 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:49 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	key_press(int keycode, t_player *player)
{
	if (keycode == ESC)
		close_window(NULL);
	handle_movement_keys_press(keycode, player);
	handle_rotation_keys_press(keycode, player);
	handle_weapon_keys_press(keycode, player);
	handle_action_keys_press(keycode, player);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	handle_movement_keys_release(keycode, player);
	handle_rotation_keys_release(keycode, player);
	return (0);
}

void	handle_movement_keys_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
}

void	handle_movement_keys_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
}

void	handle_rotation_keys_press(int keycode, t_player *player)
{
	if (keycode == Q)
		player->left_rotate = true;
	if (keycode == E)
		player->right_rotate = true;
	if (keycode == R)
		player->turn_back = true;
	if (keycode == LEFT)
		player->left = true;
	if (keycode == RIGHT)
		player->right = true;
}
