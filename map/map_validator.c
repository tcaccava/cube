/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:55 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/12 11:21:38 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
		while (map->matrix[y][x] && x < (int)ft_strlen(map->matrix[y]))
		{
			if (is_valid_playable_char(map->matrix[y][x]))
			{
				if (y == 0 || y == map->height - 1 || x == 0
					|| x >= (int)ft_strlen(map->matrix[y]) - 1)
					return (printf("Error: Invalid Map\n"), 0);
				if (!check_surrounding_spaces(map, x, y))
					return (printf("Error: Invalid Map\n"), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!check_map(map))
		return (0);
	if (!check_borders(map))
		return (0);
	if (!check_playable_spaces(map))
		return (0);
	return (1);
}

int	valid_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D' || c == 'd'
		|| c == 'M' || c == '0' || c == '1' || c == 'G' || c == 'R' || c == 'H'
		|| c == 'L' || c == ' ');
}

int	check_map(t_map *map)
{
	int	x;
	int	y;
	int	row_length;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		row_length = ft_strlen(map->matrix[y]);
		while (x < row_length)
		{
			if (!valid_char(map->matrix[y][x]))
			{
				printf("Error: invalid char '%c' at position (%d, %d)\n",
					map->matrix[y][x], x, y);
				return (0);
			}
			x++;
		}
		y++;
	}
	if (!validate_player_spawn_count(map))
		return (0);
	return (1);
}
