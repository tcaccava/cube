/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:36 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:37 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	cast_vertical_ray(t_intersect *v, t_map *map)
{
	int	iter;
	int	max_iterations;

	iter = 0;
	max_iterations = 1000;
	while (iter < max_iterations)
	{
		if (!is_not_wall(map, v->x, v->y))
			break ;
		v->x += v->step_x;
		v->y += v->step_y;
		iter++;
	}
}

static void	cast_horizontal_ray(t_intersect *h, t_map *map)
{
	int	iter;
	int	max_iterations;

	iter = 0;
	max_iterations = 1000;
	while (iter < max_iterations)
	{
		if (!is_not_wall(map, h->x, h->y))
			break ;
		h->x += h->step_x;
		h->y += h->step_y;
		iter++;
	}
}

static double	handle_ray_result(t_game *game, t_intersect *v, t_intersect *h,
		int column_x)
{
	double			dis_v;
	double			dis_h;
	t_ray_hit_data	hit_data;

	dis_v = sqrt(pow(v->x - game->player.x, 2) + pow(v->y - game->player.y, 2));
	dis_h = sqrt(pow(h->x - game->player.x, 2) + pow(h->y - game->player.y, 2));
	if (fabs(dis_v - dis_h) < 0.00001)
	{
		hit_data = (t_ray_hit_data){dis_h, h->x, h->y, 0,
			get_hit_type(&game->map, h->x, h->y)};
		store_ray_info(game, column_x, &hit_data);
		return (dis_h);
	}
	if (dis_v < dis_h)
	{
		hit_data = (t_ray_hit_data){dis_v, v->x, v->y, 1,
			get_hit_type(&game->map, v->x, v->y)};
		store_ray_info(game, column_x, &hit_data);
		return (dis_v);
	}
	hit_data = (t_ray_hit_data){dis_h, h->x, h->y, 0,
		get_hit_type(&game->map, h->x, h->y)};
	store_ray_info(game, column_x, &hit_data);
	return (dis_h);
}

double	ray_casting(t_game *game, double radiant_angle, int column_x)
{
	t_intersect	v;
	t_intersect	h;

	radiant_angle = normalize_angle(radiant_angle);
	v = v_intersection(game->player.x, game->player.y, radiant_angle);
	h = h_intersection(game->player.x, game->player.y, radiant_angle);
	cast_vertical_ray(&v, &game->map);
	cast_horizontal_ray(&h, &game->map);
	return (handle_ray_result(game, &v, &h, column_x));
}
