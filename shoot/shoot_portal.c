/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:45 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:17:46 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	shoot_portalgun(t_game *game)
{
	if (game->portal_count < 2)
		calculate_shoot(game);
}

int	calculate_portal_orientation(t_ray *center_ray)
{
	if (center_ray->hit_vertical)
	{
		if (cos(center_ray->radiant_angle) > 0)
			return (1);
		else
			return (3);
	}
	else
	{
		if (sin(center_ray->radiant_angle) > 0)
			return (2);
		else
			return (0);
	}
}

void	handle_portal_shot(t_game *game, t_ray *center_ray)
{
	double	impact_x;
	double	impact_y;
	int		map_x;
	int		map_y;
	int		portal_orientation;

	if (center_ray->hit_type != '1')
		return ;
	impact_x = center_ray->wall_hit_x;
	impact_y = center_ray->wall_hit_y;
	map_x = (int)(impact_x / TILE_SIZE);
	map_y = (int)(impact_y / TILE_SIZE);
	portal_orientation = calculate_portal_orientation
		(center_ray);
	create_portal(game, map_x, map_y, portal_orientation);
}
