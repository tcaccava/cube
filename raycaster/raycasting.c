/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:09:42 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 23:38:44 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	init_vertical_intersection(t_intersect *v, int x_player,
		int y_player, double radiant_angle)
{
	double	first_x;
	double	first_y;

	v->x = x_player;
	v->y = y_player;
	v->step_x = 0;
	v->step_y = 0;
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

	if (fabs(cos(radiant_angle)) < 0.000001)
	{
		v.x = x_player;
		v.y = y_player;
		v.step_x = 0;
		v.step_y = 0;
		return (v);
	}
	init_vertical_intersection(&v, x_player, y_player, radiant_angle);
	return (v);
}

static void	init_horizontal_intersection(t_intersect *h, int x_player,
		int y_player, double radiant_angle)
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
	init_horizontal_intersection(&h, x_player, y_player, radiant_angle);
	return (h);
}

void	cast_intersections(t_game *game, t_intersect *v, t_intersect *h)
{
	int	iter;
	int	max_iter;

	max_iter = 1000;
	iter = 0;
	while (is_not_wall(&game->map, v->x, v->y) && iter < max_iter)
	{
		v->x += v->step_x;
		v->y += v->step_y;
		iter++;
	}
	iter = 0;
	while (is_not_wall(&game->map, h->x, h->y) && iter < max_iter)
	{
		h->x += h->step_x;
		h->y += h->step_y;
		iter++;
	}
}
