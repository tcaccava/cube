/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:19:50 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:51 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		center_y;
	int		delta_x;
	int		delta_y;

	center_x = DISPLAY_WIDTH / 2;
	center_y = DISPLAY_HEIGHT / 2;
	if (x == center_x && y == center_y)
		return (0);
	delta_x = x - center_x;
	delta_y = y - center_y;
	apply_mouse_rotation(game, delta_x, delta_y);
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	return (0);
}

void	apply_mouse_rotation(t_game *game, int delta_x, int delta_y)
{
	double	sensibility;

	sensibility = 0.003;
	game->player.angle += delta_x * sensibility;
	game->player.angle = normalize_angle(game->player.angle);
	game->pitch -= delta_y;
	clamp_pitch(game);
}

void	clamp_pitch(t_game *game)
{
	if (game->pitch > 300)
		game->pitch = 300;
	if (game->pitch < -300)
		game->pitch = -300;
}

void	handle_rotation_keys_release(int keycode, t_player *player)
{
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
}

void	process_rotation_keys(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.05;
	if (player->left_rotate)
		rotate_left(player, angle_speed);
	if (player->right_rotate)
		rotate_right(player, angle_speed);
	if (player->turn_back)
		turn_around(player);
}
