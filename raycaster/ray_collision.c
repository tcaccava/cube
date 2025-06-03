/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:38 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:39 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	is_solid_cell(char cell)
{
	if (cell == '1' || cell == 'D' || cell == 'P' || cell == 'i'
		|| cell == 'd' || cell == 'M')
		return (1);
	return (0);
}

static int	is_movement_blocking_cell(char cell)
{
	if (cell == '1' || cell == 'D' || cell == 'P' || cell == 'i'
		|| cell == 'd' || cell == 'M' || cell == 'L')
		return (1);
	return (0);
}

int	is_not_wall_for_movement(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (0);
	if (is_movement_blocking_cell(map->matrix[map_y][map_x]))
		return (0);
	return (1);
}

static int	check_open_door_collision(t_map *map, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;
	double	cell_x;
	double	frame_width;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	cell = map->matrix[map_y][map_x];
	if (cell == 'O' || cell == 'o')
	{
		cell_x = fmod(x, TILE_SIZE);
		frame_width = TILE_SIZE * 0.15;
		if (cell_x > frame_width && cell_x < TILE_SIZE - frame_width)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	is_not_wall(t_map *map, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (0);
	cell = map->matrix[map_y][map_x];
	if (cell == 'L')
		return (1);
	if (check_open_door_collision(map, x, y))
		return (1);
	if (is_solid_cell(cell))
		return (0);
	else
		return (1);
}
