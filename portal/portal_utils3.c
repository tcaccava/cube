/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:58 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:00 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	calculate_distance_to_portal(t_game *game, double portal_x,
			double portal_y)
{
	double	dx;
	double	dy;
	double	distance;

	dx = game->player.x - portal_x;
	dy = game->player.y - portal_y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}
