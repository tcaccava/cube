/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:25 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:26 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	setup_weapon_at_position(t_game *game, int x, int y, int *weapon_index)
{
	char	cell;

	game->weapon_pickup[*weapon_index].x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->weapon_pickup[*weapon_index].y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	cell = game->map.matrix[y][x];
	if (cell == 'R')
		setup_raygun_pickup(game, *weapon_index);
	else if (cell == 'G')
		setup_portalgun_pickup(game, *weapon_index);
	else if (cell == 'H')
		setup_healgun_pickup(game, *weapon_index);
	game->weapon_pickup[*weapon_index].active = 1;
	(*weapon_index)++;
}

void	setup_raygun_pickup(t_game *game, int index)
{
	game->weapon_pickup[index].weapon_type = RAYGUN;
	if (!load_weapon_pickup_sprite(game, &game->weapon_pickup[index],
			"./texture/raygun_pickup.xpm"))
		printf("Warning: raygun_pickup.xpm not found\n");
}

void	setup_portalgun_pickup(t_game *game, int index)
{
	game->weapon_pickup[index].weapon_type = PORTALGUN;
	if (!load_weapon_pickup_sprite(game, &game->weapon_pickup[index],
			"./texture/portalgun_pickup.xpm"))
		printf("Warning: portalgun_pickup.xpm not found\n");
}

void	setup_healgun_pickup_weapon(t_game *game, int index)
{
	game->weapon_pickup[index].weapon_type = HEALGUN;
	if (!load_weapon_pickup_sprite(game, &game->weapon_pickup[index],
			"./texture/healgun_pickup.xpm"))
		printf("Warning: healgun_pickup.xpm not found\n");
}
