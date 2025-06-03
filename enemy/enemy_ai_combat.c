/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_combat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:03 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:04 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	check_enemy_recursive(t_game *game, int old_x, int old_y, int index)
{
	if (index >= game->num_enemies)
		return (0);
	if (game->enemies[index].active
		&& (int)(game->enemies[index].x) == old_x
		&& (int)(game->enemies[index].y) == old_y)
		return (1);
	return (check_enemy_recursive(game, old_x, old_y, index + 1));
}

static int	check_enemy_exists_at_position(t_game *game, int old_x, int old_y)
{
	return (check_enemy_recursive(game, old_x, old_y, 0));
}

static void	handle_new_enemy_position(t_game *game, t_enemy *enemy,
		int new_map_x, int new_map_y)
{
	if (new_map_x < 0 || new_map_x >= game->map.width)
		return ;
	if (new_map_y < 0 || new_map_y >= game->map.height)
		return ;
	if (!enemy->active)
		return ;
	game->map.matrix[new_map_y][new_map_x] = 'M';
}

void	handle_old_enemy_position(t_game *game, int old_map_x, int old_map_y)
{
	if (old_map_x < 0 || old_map_x >= game->map.width)
		return ;
	if (old_map_y < 0 || old_map_y >= game->map.height)
		return ;
	if (game->map.matrix[old_map_y][old_map_x] != 'M')
		return ;
	if (!check_enemy_exists_at_position(game, old_map_x, old_map_y))
		game->map.matrix[old_map_y][old_map_x] = '0';
}

void	update_enemy_position_on_map(t_game *game, t_enemy *enemy,
		double old_x, double old_y)
{
	int	old_map_x;
	int	old_map_y;
	int	new_map_x;
	int	new_map_y;

	old_map_x = (int)(old_x);
	old_map_y = (int)(old_y);
	new_map_x = (int)(enemy->x);
	new_map_y = (int)(enemy->y);
	if (old_map_x == new_map_x && old_map_y == new_map_y)
		return ;
	handle_old_enemy_position(game, old_map_x, old_map_y);
	handle_new_enemy_position(game, enemy, new_map_x, new_map_y);
}
