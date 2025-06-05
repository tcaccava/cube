/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:55 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 16:56:28 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_borders(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (y == 0 || y == map->height - 1)
		{
			x = 0;
			while (x < map->width)
			{
				if (map->matrix[y][x] != '1')
					return (printf("Error: Invalid Map"));
				x++;
			}
		}
		else if ((map->matrix[y][0] != '1') || (map->matrix[y][map->width
			- 1] != '1'))
			return (printf("Error: Invalid Map"));
		y++;
	}
	return (1);
}

int	is_valid_playable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_surrounding_spaces(t_map *map, int x, int y)
{
	int	dx;
	int	dy;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (map->matrix[y + dy][x + dx] == ' ')
				return (0);
			dx++;
		}
		dy++;
	}
	return (1);
}

int	check_playable_spaces(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_valid_playable_char(map->matrix[y][x]))
			{
				if (y == 0 || y == map->height - 1 || x == 0
					|| x == map->width - 1)
					return (printf("Error: Invalid Map\n"));
				if (!check_surrounding_spaces(map, x, y))
					return (printf("Error: Invalid Map\n"));
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!check_borders(map))
		return (0);
	if (!check_playable_spaces(map))
		return (0);
	return (1);
}
