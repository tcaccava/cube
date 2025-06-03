/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:54 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:55 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

char	*get_orientation_name(int orientation)
{
	if (orientation == 0)
		return ("North");
	else if (orientation == 1)
		return ("East");
	else if (orientation == 2)
		return ("South");
	else
		return ("West");
}

int	is_valid_map_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width)
		return (0);
	if (y < 0 || y >= game->map.height)
		return (0);
	return (1);
}

int	is_valid_teleport_position(t_game *game, int x, int y)
{
	if (!is_valid_map_position(game, x, y))
		return (0);
	if (game->map.matrix[y][x] != '0')
		return (0);
	return (1);
}

void	place_player_at_position(t_game *game, int x, int y)
{
	game->player.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->player.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
}

int	try_teleport_at_direction(t_game *game, int dest_x, int dest_y, int dir)
{
	int	adj_offsets[4][2];
	int	adj_x;
	int	adj_y;

	init_adjacent_offsets(adj_offsets);
	adj_x = dest_x + adj_offsets[dir][0];
	adj_y = dest_y + adj_offsets[dir][1];
	if (is_valid_teleport_position(game, adj_x, adj_y))
	{
		place_player_at_position(game, adj_x, adj_y);
		printf("Portal teleportation successful!\n");
		return (1);
	}
	return (0);
}
