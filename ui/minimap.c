/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:09 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:17:10 by abkhefif         ###   ########.fr       */
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

static int	is_border_pixel(t_minimap *mini_map, int x, int y)
{
	if (x < mini_map->x + mini_map->border)
		return (1);
	if (x >= mini_map->x + mini_map->size - mini_map->border)
		return (1);
	if (y < mini_map->y + mini_map->border)
		return (1);
	if (y >= mini_map->y + mini_map->size - mini_map->border)
		return (1);
	return (0);
}

static void	draw_background_pixel(t_game *game, t_minimap *mini_map
		, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	if (is_border_pixel(mini_map, x, y))
		color = mini_map->border_color;
	else
		color = mini_map->bg_color;
	pixel = game->screen.addr + (y * game->screen.line_length
			+ x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	draw_minimap_background(t_game *game)
{
	t_minimap	*mini_map;
	int			x;
	int			y;

	mini_map = &game->minimap;
	y = mini_map->y;
	while (y < mini_map->y + mini_map->size)
	{
		x = mini_map->x;
		while (x < mini_map->x + mini_map->size)
		{
			draw_background_pixel(game, mini_map, x, y);
			x++;
		}
		y++;
	}
}

unsigned int	get_cell_color(t_minimap *mini_map, char cell_type)
{
	if (cell_type == '1')
		return (mini_map->wall_color);
	if (cell_type == 'D')
		return (mini_map->door_color);
	if (cell_type == 'P')
		return (mini_map->portal_color);
	return (mini_map->bg_color);
}
