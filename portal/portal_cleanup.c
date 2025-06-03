/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:46 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:47 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	remove_all_portals(t_game *game)
{
	clear_portals_from_map(game);
	reset_portal_states(game);
	recalculate_rays(game);
}

void	clear_portals_from_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.matrix[y][x] == 'P')
				game->map.matrix[y][x] = '1';
			x++;
		}
		y++;
	}
}

void	reset_portal_states(t_game *game)
{
	game->portal_count = 0;
	game->portal_1.is_active = 0;
	game->portal_2.is_active = 0;
}

void	recalculate_rays(t_game *game)
{
	int		i;
	double	ray_offset;
	double	radiant_angle;

	i = 0;
	while (i < DISPLAY_WIDTH)
	{
		ray_offset = game->player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
		radiant_angle = normalize_angle(game->player.angle + ray_offset);
		update_ray_data(game, i, radiant_angle);
		i++;
	}
}

void	update_ray_data(t_game *game, int i, double radiant_angle)
{
	game->rays[i].radiant_angle = radiant_angle;
	game->rays[i].player_angle = game->player.angle;
	game->rays[i].distance = ray_casting(game, radiant_angle, i);
}
