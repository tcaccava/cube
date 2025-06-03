/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:48 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:49 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	create_portal(t_game *game, int map_x, int map_y, int orientation)
{
	if (game->portal_count < 2)
		return (create_new_portal(game, map_x, map_y, orientation));
	else
		return (reset_and_create_portal(game, map_x, map_y, orientation));
}

int	create_new_portal(t_game *game, int map_x, int map_y, int orientation)
{
	game->map.matrix[map_y][map_x] = 'P';
	if (game->portal_count == 0)
		setup_portal_one(game, map_x, map_y, orientation);
	else
		setup_portal_two(game, map_x, map_y, orientation);
	game->portal_count++;
	print_portal_created(game->portal_count, map_x, map_y, orientation);
	return (1);
}

int	reset_and_create_portal(t_game *game, int map_x, int map_y, int orientation)
{
	remove_all_portals(game);
	game->map.matrix[map_y][map_x] = 'P';
	setup_portal_one(game, map_x, map_y, orientation);
	game->portal_count = 1;
	print_portal_reset(map_x, map_y, orientation);
	return (1);
}

void	print_portal_created(int portal_num, int x, int y, int orientation)
{
	char	*direction;

	direction = get_orientation_name(orientation);
	printf("Portal %d created at [%d, %d], orientation: %s\n",
		portal_num, x, y, direction);
}

void	print_portal_reset(int x, int y, int orientation)
{
	char	*direction;

	direction = get_orientation_name(orientation);
	printf("New portals, first at [%d, %d], orientation: %s\n",
		x, y, direction);
}
