/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:43:13 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:03:08 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	clear_old_enemy_position(t_game *game, int old_map_x, int old_map_y)
{
	int	i;
	int	nemico_presente;

	if (game->map.matrix[old_map_y][old_map_x] != 'M')
		return ;
	nemico_presente = 0;
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].active && (int)(game->enemies[i].x) == old_map_x
			&& (int)(game->enemies[i].y) == old_map_y)
		{
			nemico_presente = 1;
			break ;
		}
		i++;
	}
	if (!nemico_presente)
		game->map.matrix[old_map_y][old_map_x] = '0';
}

void	update_enemy_position_on_map(t_game *game, t_enemy *enemy, double old_x,
		double old_y)
{
	int	old_map_x;
	int	old_map_y;
	int	new_map_x;
	int	new_map_y;

	old_map_x = (int)(old_x);
	old_map_y = (int)(old_y);
	new_map_x = (int)(enemy->x);
	new_map_y = (int)(enemy->y);
	if (old_map_x != new_map_x || old_map_y != new_map_y)
	{
		if (old_map_x >= 0 && old_map_x < game->map.width && old_map_y >= 0
			&& old_map_y < game->map.height)
			clear_old_enemy_position(game, old_map_x, old_map_y);
		if (new_map_x >= 0 && new_map_x < game->map.width && new_map_y >= 0
			&& new_map_y < game->map.height && enemy->active)
			game->map.matrix[new_map_y][new_map_x] = 'M';
	}
}
