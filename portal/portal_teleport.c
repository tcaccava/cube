/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_teleport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:52 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:53 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	teleport_through_portal(t_game *game, int portal_x, int portal_y)
{
	t_portal	*dest_portal;

	if (game->portal_count != 2)
		return ;
	dest_portal = get_destination_portal(game, portal_x, portal_y);
	if (!dest_portal)
		return ;
	execute_teleportation(game, dest_portal);
}

t_portal	*get_destination_portal(t_game *game, int portal_x, int portal_y)
{
	int	portal_1_map_x;
	int	portal_1_map_y;
	int	portal_2_map_x;
	int	portal_2_map_y;

	portal_1_map_x = (int)(game->portal_1.x / TILE_SIZE);
	portal_1_map_y = (int)(game->portal_1.y / TILE_SIZE);
	portal_2_map_x = (int)(game->portal_2.x / TILE_SIZE);
	portal_2_map_y = (int)(game->portal_2.y / TILE_SIZE);
	if (portal_x == portal_1_map_x && portal_y == portal_1_map_y)
		return (&game->portal_2);
	else if (portal_x == portal_2_map_x && portal_y == portal_2_map_y)
		return (&game->portal_1);
	return (NULL);
}

void	execute_teleportation(t_game *game, t_portal *dest_portal)
{
	int	exit_direction;
	int	dest_x;
	int	dest_y;

	exit_direction = calculate_exit_direction(dest_portal);
	dest_x = (int)(dest_portal->x / TILE_SIZE);
	dest_y = (int)(dest_portal->y / TILE_SIZE);
	if (try_teleport_at_direction(game, dest_x, dest_y, exit_direction))
	{
		remove_all_portals(game);
		return ;
	}
	remove_all_portals(game);
	emergency_teleport(game, dest_portal);
}

int	calculate_exit_direction(t_portal *dest_portal)
{
	return ((dest_portal->orientation + 2) % 4);
}

void	emergency_teleport(t_game *game, t_portal *dest_portal)
{
	game->player.x = dest_portal->x;
	game->player.y = dest_portal->y + 30;
	printf("Emergency portal teleportation used!\n");
}
