/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:53 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:54 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_player_spawn(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void	set_player_angle(t_player *player, char direction)
{
	if (direction == 'N')
		player->angle = 3 * M_PI / 2;
	else if (direction == 'E')
		player->angle = 0;
	else if (direction == 'S')
		player->angle = M_PI / 2;
	else if (direction == 'W')
		player->angle = M_PI;
}

void	set_player_position(t_game *game, int x, int y, char direction)
{
	game->player.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->player.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	set_player_angle(&game->player, direction);
	game->map.matrix[y][x] = '0';
}

int	set_player_pos(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_player_spawn(game->map.matrix[y][x]))
			{
				set_player_position(game, x, y, game->map.matrix[y][x]);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
