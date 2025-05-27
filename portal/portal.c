/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:53:54 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 21:55:21 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cube3d.h"

static void	clear_portals(t_game *game)
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
	game->portal_count = 0;
}

void	remove_all_portals(t_game *game)
{
	int		i;
	double	ray_offset;
	double	radiant_angle;

	i = 0;
	clear_portals(game);
	while (i < DISPLAY_WIDTH)
	{
		ray_offset = game->player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
		radiant_angle = normalize_angle(game->player.angle + ray_offset);
		game->rays[i].radiant_angle = radiant_angle;
		game->rays[i].player_angle = game->player.angle;
		game->rays[i].distance = ray_casting(game, radiant_angle, i);
		i++;
	}
}
