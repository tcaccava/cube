/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:29:18 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:52:24 by tcaccava         ###   ########.fr       */
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

static int	is_invalid_tile(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		return (1);
	if (map->matrix[y - 1][x - 1] == ' ' || map->matrix[y - 1][x] == ' '
		|| map->matrix[y - 1][x + 1] == ' ' || map->matrix[y][x - 1] == ' '
		|| map->matrix[y][x + 1] == ' ' || map->matrix[y + 1][x - 1] == ' '
		|| map->matrix[y + 1][x] == ' ' || map->matrix[y + 1][x + 1] == ' ')
		return (1);
	return (0);
}

int	check_playable_spaces(t_map *map)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tile = map->matrix[y][x];
			if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E'
				|| tile == 'W')
			{
				if (is_invalid_tile(map, x, y))
					return (printf("Error: Invalid Map"));
			}
			x++;
		}
		y++;
	}
	return (1);
}

static void	set_player_angle_and_position(t_game *game, int x, int y, char dir)
{
	game->player.x = x * TILE_SIZE + TILE_SIZE / 2;
	game->player.y = y * TILE_SIZE + TILE_SIZE / 2;
	if (dir == 'N')
		game->player.angle = 3 * M_PI / 2;
	else if (dir == 'E')
		game->player.angle = 0;
	else if (dir == 'S')
		game->player.angle = M_PI / 2;
	else if (dir == 'W')
		game->player.angle = M_PI;
}

int	set_player_pos(t_game *game)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			tile = game->map.matrix[y][x];
			if (tile == 'N' || tile == 'E' || tile == 'S' || tile == 'W')
			{
				set_player_angle_and_position(game, x, y, tile);
				game->map.matrix[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
