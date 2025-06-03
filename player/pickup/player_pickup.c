/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pickup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:10 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:11 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	check_weapon_pickup(t_player *player)
{
	int		player_map_x;
	int		player_map_y;
	char	cell_type;

	if (!player->game)
		return ;
	player_map_x = (int)(player->x / TILE_SIZE);
	player_map_y = (int)(player->y / TILE_SIZE);
	if (!is_valid_pickup_position(player->game, player_map_x, player_map_y))
		return ;
	cell_type = player->game->map.matrix[player_map_y][player_map_x];
	process_weapon_pickup(player, cell_type, player_map_x, player_map_y);
}

void	process_weapon_pickup(t_player *player, char cell_type,
		int map_x, int map_y)
{
	if (cell_type == 'R')
		pickup_raygun(player, map_x, map_y);
	else if (cell_type == 'G')
		pickup_portalgun(player, map_x, map_y);
	else if (cell_type == 'H')
		pickup_healgun(player, map_x, map_y);
}

void	pickup_raygun(t_player *player, int map_x, int map_y)
{
	if (!player->has_weapon[RAYGUN])
	{
		player->has_weapon[RAYGUN] = true;
		player->game->map.matrix[map_y][map_x] = '0';
		player->current_weapon = RAYGUN;
		player->game->current_weapon = RAYGUN;
		disable_weapon_pickup_at_position(player->game, map_x, map_y, RAYGUN);
	}
}

void	pickup_portalgun(t_player *player, int map_x, int map_y)
{
	if (!player->has_weapon[PORTALGUN])
	{
		player->has_weapon[PORTALGUN] = true;
		player->current_weapon = PORTALGUN;
		player->game->current_weapon = PORTALGUN;
		disable_weapon_pickup_at_position(player->game,
			map_x, map_y, PORTALGUN);
	}
}

void	pickup_healgun(t_player *player, int map_x, int map_y)
{
	if (!player->has_weapon[HEALGUN])
		pickup_healgun_first_time(player, map_x, map_y);
	else
		pickup_healgun_ammo(player, map_x, map_y);
}
