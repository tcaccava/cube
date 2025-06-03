/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:41 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:42 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	calculate_vertical_first_intersection(int x_player, int y_player,
			double radiant_angle, t_intersect *v)
{
	double	first_x;
	double	first_y;

	if (cos(radiant_angle) > 0)
	{
		first_x = floor(x_player / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		v->step_x = TILE_SIZE;
	}
	else
	{
		first_x = floor(x_player / TILE_SIZE) * TILE_SIZE;
		v->step_x = -TILE_SIZE;
		first_x -= 0.001;
	}
	first_y = y_player + (first_x - x_player) * tan(radiant_angle);
	v->step_y = tan(radiant_angle) * v->step_x;
	v->x = first_x;
	v->y = first_y;
}

t_intersect	v_intersection(int x_player, int y_player, double radiant_angle)
{
	t_intersect	v;

	v.x = x_player;
	v.y = y_player;
	v.step_x = 0;
	v.step_y = 0;
	if (fabs(cos(radiant_angle)) < 0.000001)
		return (v);
	calculate_vertical_first_intersection(x_player, y_player,
		radiant_angle, &v);
	return (v);
}

static void	calculate_horizontal_first_intersection(int x_player, int y_player,
			double radiant_angle, t_intersect *h)
{
	double	first_x;
	double	first_y;

	if (sin(radiant_angle) > 0)
	{
		first_y = floor(y_player / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		h->step_y = TILE_SIZE;
	}
	else
	{
		first_y = floor(y_player / TILE_SIZE) * TILE_SIZE;
		h->step_y = -TILE_SIZE;
		first_y -= 0.001;
	}
	if (fabs(tan(radiant_angle)) > 0.000001)
		first_x = x_player + (first_y - y_player) / tan(radiant_angle);
	else
		first_x = x_player;
	h->step_x = h->step_y / tan(radiant_angle);
	h->x = first_x;
	h->y = first_y;
}

t_intersect	h_intersection(int x_player, int y_player, double radiant_angle)
{
	t_intersect	h;

	h.x = x_player;
	h.y = y_player;
	h.step_x = 0;
	h.step_y = 0;
	if (fabs(sin(radiant_angle)) < 0.000001)
		return (h);
	calculate_horizontal_first_intersection(x_player, y_player,
		radiant_angle, &h);
	return (h);
}
