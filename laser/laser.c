/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:58 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:59 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_laser_hit(t_game *game, double ray_x, double ray_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(ray_x / TILE_SIZE);
	map_y = (int)(ray_y / TILE_SIZE);
	if (map_x >= 0 && map_x < game->map.width
		&& map_y >= 0 && map_y < game->map.height)
	{
		if (game->map.matrix[map_y][map_x] == 'L')
			return (1);
	}
	return (0);
}

static int	check_wall_hit(t_game *game, double ray_x, double ray_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(ray_x / TILE_SIZE);
	map_y = (int)(ray_y / TILE_SIZE);
	if (map_x >= 0 && map_x < game->map.width
		&& map_y >= 0 && map_y < game->map.height
		&& game->map.matrix[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	ray_crosses_laser(t_game *game, double radiant_angle)
{
	double	ray_x;
	double	ray_y;
	double	ray_dx;
	double	ray_dy;
	double	distance;

	ray_x = game->player.x;
	ray_y = game->player.y;
	ray_dx = cos(radiant_angle);
	ray_dy = sin(radiant_angle);
	distance = 0;
	while (distance < 800.0)
	{
		ray_x += ray_dx * 5.0;
		ray_y += ray_dy * 5.0;
		if (check_laser_hit(game, ray_x, ray_y))
			return (1);
		if (check_wall_hit(game, ray_x, ray_y))
			break ;
		distance += 5.0;
	}
	return (0);
}

void	init_laser_positions(int *positions, int center_y)
{
	positions[0] = center_y - 100;
	positions[1] = center_y - 50;
	positions[2] = center_y;
	positions[3] = center_y + 50;
	positions[4] = center_y + 100;
}
