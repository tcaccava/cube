/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:39:35 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 21:26:59 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_file_cub(char *file_path)
{
	int	i;

	i = ft_strlen(file_path);
	if (i < 4)
		return (0);
	if (file_path[i - 4] == '.' && file_path[i - 3] == 'c' && file_path[i
			- 2] == 'u' && file_path[i - 1] == 'b')
		return (1);
	return (0);
}

void	init_enemy_at(t_game *game, int y, int x, int *idx)
{
	game->enemies[*idx].x = x * TILE_SIZE + TILE_SIZE / 2;
	game->enemies[*idx].y = y * TILE_SIZE + TILE_SIZE / 2;
	game->enemies[*idx].active = 1;
	game->enemies[*idx].state = IDLE;
	game->enemies[*idx].health = 50;
	game->enemies[*idx].speed = 2.0;
	game->enemies[*idx].sees_player = 0;
	game->enemies[*idx].angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
	game->map.matrix[y][x] = '0';
	(*idx)++;
}

int	set_enemy_poss(t_game *game)
{
	int	y;
	int	x;
	int	idx;

	idx = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.matrix[y][x] == 'M' && idx < game->num_enemies)
				init_enemy_at(game, y, x, &idx);
			x++;
		}
		y++;
	}
	return (idx > 0);
}
