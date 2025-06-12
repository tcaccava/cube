/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:38 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/12 13:09:54 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	is_solid_cell(char cell)
{
	if (cell == '1' || cell == 'D' || cell == 'P' || cell == 'i' || cell == 'd'
		|| cell == 'M')
		return (1);
	return (0);
}

static int	is_movement_blocking_cell(char cell)
{
	if (cell == '1' || cell == 'D' || cell == 'P' || cell == 'i' || cell == 'd'
		|| cell == 'M' || cell == 'L')
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

static int	check_open_door_collision(t_map *m, double x, double y)
{
	int		xi;
	int		yi;
	double	cx;
	double	fw;
	char	cell;

	xi = (int)(x / TILE_SIZE);
	yi = (int)(y / TILE_SIZE);
	if (yi < 0 || yi >= m->height || xi < 0
		|| xi >= (int)ft_strlen(m->matrix[yi]))
		return (0);
	cell = m->matrix[yi][xi];
	if (cell != 'O' && cell != 'o')
		return (0);
	cx = fmod(x, TILE_SIZE);
	fw = TILE_SIZE * 0.15;
	return (cx > fw && cx < TILE_SIZE - fw);
}

int	is_not_wall(t_map *m, double x, double y)
{
	int		xi;
	int		yi;
	char	c;

	xi = (int)(x / TILE_SIZE);
	yi = (int)(y / TILE_SIZE);
	if (yi < 0 || yi >= m->height || xi < 0
		|| xi >= (int)ft_strlen(m->matrix[yi]))
		return (0);
	c = m->matrix[yi][xi];
	if (c == 'L' || check_open_door_collision(m, x, y))
		return (1);
	return (!is_solid_cell(c));
}
