/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:29:59 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 19:53:32 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	is_pixel_in_bounds(t_minimap *mini_map, int x, int y)
{
	return (x >= mini_map->x + mini_map->border && x < mini_map->x
		+ mini_map->size - mini_map->border && y >= mini_map->y
		+ mini_map->border && y < mini_map->y + mini_map->size
		- mini_map->border);
}

static void	draw_circle_pixel(t_game *game, int x, int y)
{
	t_minimap	*mini_map;
	char		*pixel;

	mini_map = &game->minimap;
	if (is_pixel_in_bounds(mini_map, x, y))
	{
		pixel = game->screen.addr + (y * game->screen.line_length + x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = mini_map->player_color;
	}
}

void	draw_player_circle(t_game *game, int center_x, int center_y)
{
	int	player_size;
	int	px;
	int	py;
	int	x;
	int	y;

	player_size = 4;
	py = -player_size;
	while (py <= player_size)
	{
		px = -player_size;
		while (px <= player_size)
		{
			if (px * px + py * py <= player_size * player_size)
			{
				x = center_x + px;
				y = center_y + py;
				draw_circle_pixel(game, x, y);
			}
			px++;
		}
		py++;
	}
}

void	draw_minimap_player(t_game *game)
{
	t_minimap	*mini_map;
	int			center_x;
	int			center_y;

	mini_map = &game->minimap;
	center_x = mini_map->x + mini_map->size / 2;
	center_y = mini_map->y + mini_map->size / 2;
	draw_player_circle(game, center_x, center_y);
	draw_minimap_cone(game);
}
