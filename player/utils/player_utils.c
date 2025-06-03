/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:14 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:15 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->map.width)
		return (1);
	if (map_y < 0 || map_y >= game->map.height)
		return (1);
	return (!is_not_wall_for_movement(&game->map, x, y));
}

void	update_player_position(t_player *player)
{
	check_portal_teleportation(player->game);
	check_weapon_pickup(player);
}

int	validate_player_game(t_player *player)
{
	if (!player)
		return (0);
	if (!player->game)
		return (0);
	return (1);
}

int	can_move_to_position(t_game *game, float x, float y)
{
	if (!game)
		return (0);
	return (is_not_wall_for_movement(&game->map, x, y));
}

void	apply_movement_bounds(t_player *player, float *new_x, float *new_y)
{
	if (!validate_player_game(player))
		return ;
	if (!can_move_to_position(player->game, *new_x, player->y))
		*new_x = player->x;
	if (!can_move_to_position(player->game, player->x, *new_y))
		*new_y = player->y;
}
