/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:26:27 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:28:39 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_minimap(t_game *game)
{
	game->minimap.size = 150;
	game->minimap.x = 20;
	game->minimap.y = DISPLAY_HEIGHT - game->minimap.size - 20;
	game->minimap.cell_size = 10;
	game->minimap.border = 2;
	game->minimap.visible_radius = (game->minimap.size - 2
			* game->minimap.border) / (2 * game->minimap.cell_size);
	game->minimap.show = 1;
	game->minimap.border_color = 0xFFFFFF;
	game->minimap.bg_color = 0x000000;
	game->minimap.wall_color = 0x888888;
	game->minimap.door_color = 0x8B4513;
	game->minimap.portal_color = 0x00FFFF;
	game->minimap.player_color = 0xFF0000;
}
