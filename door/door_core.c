/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:44 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:45 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	open_door(t_game *game)
{
	double	check_x;
	double	check_y;
	int		map_x;
	int		map_y;
	char	cell;

	calculate_door_check_position(game, &check_x, &check_y);
	map_x = (int)(check_x / TILE_SIZE);
	map_y = (int)(check_y / TILE_SIZE);
	if (!is_valid_door_position(game, map_x, map_y))
		return ;
	cell = game->map.matrix[map_y][map_x];
	toggle_door_state(game, map_x, map_y, cell);
}

void	calculate_door_check_position(t_game *game, double *check_x,
		double *check_y)
{
	double	player_x;
	double	player_y;
	double	player_angle;
	double	check_distance;

	player_x = game->player.x;
	player_y = game->player.y;
	player_angle = game->player.angle;
	check_distance = TILE_SIZE * 1.5;
	*check_x = player_x + cos(player_angle) * check_distance;
	*check_y = player_y + sin(player_angle) * check_distance;
}

int	is_valid_door_position(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map.width)
		return (0);
	if (map_y < 0 || map_y >= game->map.height)
		return (0);
	return (1);
}

void	toggle_door_state(t_game *game, int map_x, int map_y, char cell)
{
	if (cell == 'D')
	{
		printf("🚪 Ouverture de la porte à [%d,%d]\n", map_x, map_y);
		game->map.matrix[map_y][map_x] = 'O';
	}
	else if (cell == 'O')
	{
		printf("🚪 Fermeture de la porte à [%d,%d]\n", map_x, map_y);
		game->map.matrix[map_y][map_x] = 'D';
	}
}

t_open_door	*find_door_at_position(t_game *game, int map_x, int map_y)
{
	int	i;
	int	door_map_x;
	int	door_map_y;

	i = 0;
	while (i < game->num_open_doors)
	{
		door_map_x = (int)(game->open_doors[i].x / TILE_SIZE);
		door_map_y = (int)(game->open_doors[i].y / TILE_SIZE);
		if (door_map_x == map_x && door_map_y == map_y
			&& game->open_doors[i].active)
			return (&game->open_doors[i]);
		i++;
	}
	return (NULL);
}
