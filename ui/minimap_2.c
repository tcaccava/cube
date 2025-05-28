/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:41:19 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 19:52:48 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	draw_cell_row(t_game *game, t_point center, t_point player, int row)
{
	t_cell_info	info;
	int			col;

	col = -game->minimap.visible_radius;
	while (col <= game->minimap.visible_radius)
	{
		info.game = game;
		info.map.x = player.x + col;
		info.map.y = player.y + row;
		info.cell.x = center.x + col * game->minimap.cell_size;
		info.cell.y = center.y + row * game->minimap.cell_size;
		draw_minimap_cell(info);
		col++;
	}
}

static void	draw_cells_loop(t_game *game, t_point center)
{
	t_point	player;
	int		row;

	player.x = (int)(game->player.x / TILE_SIZE);
	player.y = (int)(game->player.y / TILE_SIZE);
	row = -game->minimap.visible_radius;
	while (row <= game->minimap.visible_radius)
	{
		draw_cell_row(game, center, player, row);
		row++;
	}
}

void	draw_minimap_cells(t_game *game)
{
	t_point	center;

	center.x = game->minimap.x + game->minimap.size / 2;
	center.y = game->minimap.y + game->minimap.size / 2;
	draw_cells_loop(game, center);
}

void	minimap(t_game *game)
{
	if (!game->minimap.show)
		return ;
	draw_minimap_background(game);
	draw_minimap_cells(game);
	draw_minimap_player(game);
}

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
