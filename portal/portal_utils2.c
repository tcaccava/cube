/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:57 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:58 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_adjacent_offsets(int adj_offsets[4][2])
{
	adj_offsets[0][0] = 0;
	adj_offsets[0][1] = -1;
	adj_offsets[1][0] = 1;
	adj_offsets[1][1] = 0;
	adj_offsets[2][0] = 0;
	adj_offsets[2][1] = 1;
	adj_offsets[3][0] = -1;
	adj_offsets[3][1] = 0;
}

void	check_portal_teleportation(t_game *game)
{
	double	player_x;
	double	player_y;
	int		player_map_x;
	int		player_map_y;

	player_x = game->player.x;
	player_y = game->player.y;
	player_map_x = (int)(player_x / TILE_SIZE);
	player_map_y = (int)(player_y / TILE_SIZE);
	check_nearby_portals(game, player_map_x, player_map_y);
}

void	check_nearby_portals(t_game *game, int player_x, int player_y)
{
	int	check_offsets[9][2];
	int	i;

	init_check_offsets(check_offsets);
	i = 0;
	while (i < 9)
	{
		check_portal_at_offset(game, player_x, player_y, check_offsets[i]);
		i++;
	}
}

void	init_check_offsets(int check_offsets[9][2])
{
	check_offsets[0][0] = -1;
	check_offsets[0][1] = -1;
	check_offsets[1][0] = 0;
	check_offsets[1][1] = -1;
	check_offsets[2][0] = 1;
	check_offsets[2][1] = -1;
	check_offsets[3][0] = -1;
	check_offsets[3][1] = 0;
	check_offsets[4][0] = 0;
	check_offsets[4][1] = 0;
	check_offsets[5][0] = 1;
	check_offsets[5][1] = 0;
	check_offsets[6][0] = -1;
	check_offsets[6][1] = 1;
	check_offsets[7][0] = 0;
	check_offsets[7][1] = 1;
	check_offsets[8][0] = 1;
	check_offsets[8][1] = 1;
}

void	check_portal_at_offset(t_game *game, int player_x, int player_y,
			int offset[2])
{
	int		check_x;
	int		check_y;
	double	portal_center_x;
	double	portal_center_y;
	double	distance;

	check_x = player_x + offset[0];
	check_y = player_y + offset[1];
	if (!is_valid_map_position(game, check_x, check_y))
		return ;
	if (game->map.matrix[check_y][check_x] != 'P')
		return ;
	portal_center_x = (check_x * TILE_SIZE) + (TILE_SIZE / 2);
	portal_center_y = (check_y * TILE_SIZE) + (TILE_SIZE / 2);
	distance = calculate_distance_to_portal(game, portal_center_x,
			portal_center_y);
	if (distance < 40.0)
		teleport_through_portal(game, check_x, check_y);
}
