/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:29:20 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 23:42:48 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	fill_ray_pos(t_ray_data *d, double dist, double x, double y)
{
	d->distance = dist;
	d->hit_x = x;
	d->hit_y = y;
}

static void	fill_ray_meta(t_ray_data *d, int is_vertical, t_map *map)
{
	d->is_vertical = is_vertical;
	d->hit_type = get_hit_type(map, d->hit_x, d->hit_y);
}

void	select_ray_hit(t_game *game, t_ray_calc *calc)
{
	t_ray_data	data;
	int			use_vertical;
	double		dist_v;
	double		dist_h;
	double		epsilon;

	epsilon = 0.00001;
	dist_v = sqrt(pow(calc->v->x - game->player.x, 2) + pow(calc->v->y
				- game->player.y, 2));
	dist_h = sqrt(pow(calc->h->x - game->player.x, 2) + pow(calc->h->y
				- game->player.y, 2));
	if (fabs(dist_v - dist_h) < epsilon)
		use_vertical = 0;
	else
		use_vertical = (dist_v < dist_h);
	if (use_vertical)
		fill_ray_pos(&data, dist_v, calc->v->x, calc->v->y);
	else
		fill_ray_pos(&data, dist_h, calc->h->x, calc->h->y);
	fill_ray_meta(&data, use_vertical, &game->map);
	store_ray_info(game, calc->column_x, &data);
}
