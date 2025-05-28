/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:36:36 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 19:53:15 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	draw_minimap_pixel(t_game *game, int x, int y, t_minimap *mini_map)
{
	char			*pixel;
	unsigned int	color;

	if (x < mini_map->x + mini_map->border || x >= mini_map->x + mini_map->size
		- mini_map->border || y < mini_map->y + mini_map->border
		|| y >= mini_map->y + mini_map->size - mini_map->border)
		color = mini_map->border_color;
	else
		color = mini_map->bg_color;
	pixel = game->screen.addr + (y * game->screen.line_length + x
			* (game->screen.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	draw_minimap_background(t_game *game)
{
	int			x;
	int			y;
	t_minimap	*mini_map;

	mini_map = &game->minimap;
	y = mini_map->y;
	while (y < mini_map->y + mini_map->size)
	{
		x = mini_map->x;
		while (x < mini_map->x + mini_map->size)
		{
			draw_minimap_pixel(game, x, y, mini_map);
			x++;
		}
		y++;
	}
}

static void	draw_cell_pixel(t_game *game, int x, int y, unsigned int color)
{
	t_minimap	*m;
	char		*pixel;

	m = &game->minimap;
	if (x >= m->x + m->border && x < m->x + m->size - m->border && y >= m->y
		+ m->border && y < m->y + m->size - m->border)
	{
		pixel = game->screen.addr + (y * game->screen.line_length + x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

static void	draw_minimap_cell_pixels(t_cell_info info, unsigned int color)
{
	int	row;
	int	col;
	int	size;

	row = 0;
	size = info.game->minimap.cell_size;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			draw_cell_pixel(info.game, info.cell.x + col, info.cell.y + row,
				color);
			col++;
		}
		row++;
	}
}

void	draw_minimap_cell(t_cell_info info)
{
	t_minimap		*mini_map;
	unsigned int	cell_color;
	char			cell_type;

	mini_map = &info.game->minimap;
	if (info.map.x < 0 || info.map.x >= info.game->map.width || info.map.y < 0
		|| info.map.y >= info.game->map.height)
		return ;
	cell_type = info.game->map.matrix[info.map.y][info.map.x];
	if (cell_type == '1')
		cell_color = mini_map->wall_color;
	else if (cell_type == 'D')
		cell_color = mini_map->door_color;
	else if (cell_type == 'P')
		cell_color = mini_map->portal_color;
	else
		cell_color = mini_map->bg_color;
	draw_minimap_cell_pixels(info, cell_color);
}
