/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pickup_healgun.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:02 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:03 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	pickup_healgun_first_time(t_player *player, int map_x, int map_y)
{
	player->has_weapon[HEALGUN] = true;
	player->current_weapon = HEALGUN;
	player->game->current_weapon = HEALGUN;
	player->healgun_ammo = 1;
	player->healgun_is_loaded = 1;
	player->game->map.matrix[map_y][map_x] = '0';
	disable_weapon_pickup_at_position(player->game, map_x, map_y, HEALGUN);
	printf("💉 HEAL GUN COLLECTÉ ! (1 munition)\n");
}

void	pickup_healgun_ammo(t_player *player, int map_x, int map_y)
{
	player->healgun_ammo++;
	player->game->map.matrix[map_y][map_x] = '0';
	disable_weapon_pickup_at_position(player->game, map_x, map_y, HEALGUN);
	printf("💉 Seringue collectée ! (%d munitions)\n", player->healgun_ammo);
	reload_healgun_if_empty(player);
}

void	reload_healgun_if_empty(t_player *player)
{
	if (!player->healgun_is_loaded)
	{
		player->healgun_is_loaded = 1;
		printf("🔋 Heal Gun rechargé !\n");
	}
}

int	is_valid_pickup_position(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map.width)
		return (0);
	if (map_y < 0 || map_y >= game->map.height)
		return (0);
	return (1);
}

void	handle_action_keys_press(int keycode, t_player *player)
{
	if (keycode == F)
		open_door(player->game);
}
