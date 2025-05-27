/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:44:16 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 21:46:02 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == Q)
		player->left_rotate = false;
	if (keycode == E)
		player->right_rotate = false;
	if (keycode == R)
		player->turn_back = false;
	if (keycode == LEFT)
		player->left = false;
	if (keycode == RIGHT)
		player->right = false;
	return (0);
}

static void	set_weapon(t_player *player, int weapon)
{
	player->current_weapon = weapon;
	if (player->game)
		player->game->current_weapon = weapon;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == ESC)
		close_window(NULL);
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
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
	if (keycode == 49)
		set_weapon(player, PORTALGUN);
	if (keycode == 50)
		set_weapon(player, RAYGUN);
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		center_y;
	int		delta_x;
	int		delta_y;
	double	sensibility;

	center_x = DISPLAY_WIDTH / 2;
	center_y = DISPLAY_HEIGHT / 2;
	if (x == center_x && y == center_y)
		return (0);
	delta_x = x - center_x;
	delta_y = y - center_y;
	sensibility = 0.003;
	game->player.angle += delta_x * sensibility;
	game->player.angle = normalize_angle(game->player.angle);
	game->pitch -= delta_y;
	if (game->pitch > 300)
		game->pitch = 300;
	if (game->pitch < -300)
		game->pitch = -300;
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	return (0);
}

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (1);
	if (game->map.matrix[map_y][map_x] == '1'
		|| game->map.matrix[map_y][map_x] == 'D')
		return (1);
	return (0);
}
