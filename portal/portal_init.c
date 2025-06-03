/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:50 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:51 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_portals(t_game *game)
{
	init_portal_one(game);
	init_portal_two(game);
	game->portal_count = 0;
}

void	init_portal_one(t_game *game)
{
	game->portal_1.is_active = 0;
	game->portal_1.orientation = 0;
	game->portal_1.x = 0;
	game->portal_1.y = 0;
}

void	init_portal_two(t_game *game)
{
	game->portal_2.is_active = 0;
	game->portal_2.orientation = 0;
	game->portal_2.x = 0;
	game->portal_2.y = 0;
}

void	setup_portal_one(t_game *game, int map_x, int map_y, int orientation)
{
	game->portal_1.x = (map_x * TILE_SIZE) + (TILE_SIZE / 2);
	game->portal_1.y = (map_y * TILE_SIZE) + (TILE_SIZE / 2);
	game->portal_1.is_active = 1;
	game->portal_1.orientation = orientation;
}

void	setup_portal_two(t_game *game, int map_x, int map_y, int orientation)
{
	game->portal_2.x = (map_x * TILE_SIZE) + (TILE_SIZE / 2);
	game->portal_2.y = (map_y * TILE_SIZE) + (TILE_SIZE / 2);
	game->portal_2.is_active = 1;
	game->portal_2.orientation = orientation;
}
