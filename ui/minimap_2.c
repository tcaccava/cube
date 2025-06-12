/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:00 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/12 13:36:19 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_valid_screen_pixel(t_minimap *mini_map, int screen_pixel_x,
		int screen_pixel_y)
{
	if (screen_pixel_x < mini_map->x + mini_map->border)
		return (0);
	if (screen_pixel_x >= mini_map->x + mini_map->size - mini_map->border)
		return (0);
	if (screen_pixel_y < mini_map->y + mini_map->border)
		return (0);
	if (screen_pixel_y >= mini_map->y + mini_map->size - mini_map->border)
		return (0);
	return (1);
}

void	draw_cell_pixels(t_game *game, t_minimap *mini_map,
		unsigned int cell_color, int coords[4])
{
	char	*pixel;
	int		row;
	int		col;

	row = 0;
	while (row < mini_map->cell_size)
	{
		col = 0;
		while (col < mini_map->cell_size)
		{
			coords[2] = coords[0] + col;
			coords[3] = coords[1] + row;
			if (is_valid_screen_pixel(mini_map, coords[2], coords[3]))
			{
				pixel = game->screen.addr + (coords[3]
						* game->screen.line_length + coords[2]
						* (game->screen.bits_per_pixel / 8));
				*(unsigned int *)pixel = cell_color;
			}
			col++;
		}
		row++;
	}
}

void	draw_minimap_cell(t_game *game, int p[4])
{
	t_minimap		*mini_map;
	unsigned int	color;
	int				coords[4];

	if (p[1] < 0 || p[1] >= game->map.height)
		return ;
	if (p[0] < 0 || p[0] >= (int)ft_strlen(game->map.matrix[p[1]]))
		return ;
	mini_map = &game->minimap;
	color = get_cell_color(mini_map, game->map.matrix[p[1]][p[0]]);
	coords[0] = p[2];
	coords[1] = p[3];
	coords[2] = 0;
	coords[3] = 0;
	draw_cell_pixels(game, mini_map, color, coords);
}

static void	draw_minimap_row(t_game *game, int centers[2], int player_pos[2],
		int row)
{
	t_minimap	*mini_map;
	int			positions[4];
	int			col;

	mini_map = &game->minimap;
	col = -mini_map->visible_radius;
	while (col <= mini_map->visible_radius)
	{
		positions[0] = player_pos[0] + col;
		positions[1] = player_pos[1] + row;
		positions[2] = centers[0] + col * mini_map->cell_size;
		positions[3] = centers[1] + row * mini_map->cell_size;
		draw_minimap_cell(game, positions);
		col++;
	}
}

void	draw_minimap_cells(t_game *game)
{
	t_minimap	*mini_map;
	int			centers[2];
	int			player_pos[2];
	int			row;

	mini_map = &game->minimap;
	centers[0] = mini_map->x + mini_map->size / 2;
	centers[1] = mini_map->y + mini_map->size / 2;
	player_pos[0] = (int)(game->player.x / TILE_SIZE);
	player_pos[1] = (int)(game->player.y / TILE_SIZE);
	row = -mini_map->visible_radius;
	while (row <= mini_map->visible_radius)
	{
		draw_minimap_row(game, centers, player_pos, row);
		row++;
	}
}
