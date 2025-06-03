/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:47 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:48 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_enemy_stats(t_enemy *enemy)
{
	enemy->active = 1;
	enemy->state = IDLE;
	enemy->health = 25;
	enemy->speed = 2.0;
	enemy->sees_player = 0;
	enemy->angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
}

void	set_enemy_position(t_enemy *enemy, int x, int y)
{
	enemy->x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	enemy->y = (y * TILE_SIZE) + (TILE_SIZE / 2);
}

int	place_enemy_at_position(t_game *game, int x, int y, int *enemy_index)
{
	if (*enemy_index < game->num_enemies)
	{
		set_enemy_position(&game->enemies[*enemy_index], x, y);
		init_enemy_stats(&game->enemies[*enemy_index]);
		(*enemy_index)++;
		return (1);
	}
	return (0);
}

int	set_enemy_pos(t_game *game)
{
	int	y;
	int	x;
	int	enemy_index;

	y = 0;
	enemy_index = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.matrix[y][x] == 'M')
			{
				if (place_enemy_at_position(game, x, y, &enemy_index))
					game->map.matrix[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (enemy_index > 0);
}
