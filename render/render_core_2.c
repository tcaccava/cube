/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:45:35 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 13:45:47 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	init_renderer(t_game *game, t_render *r, t_ray *ray)
{
	r->corrected_dist = no_fish_eye(ray->distance, ray->radiant_angle,
			ray->player_angle);
	r->wall_height = calc_wall_height(r->corrected_dist);
	r->door_height = (int)(r->wall_height * 1.3);
	r->draw_start = (DISPLAY_HEIGHT / 2) - (r->wall_height / 2) + game->pitch;
	r->draw_end = (DISPLAY_HEIGHT / 2) + (r->wall_height / 2) + game->pitch;
	r->texture_offset_y = 0;
	if (r->wall_height > DISPLAY_HEIGHT)
		r->texture_offset_y = (r->wall_height - DISPLAY_HEIGHT) / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= DISPLAY_HEIGHT)
		r->draw_end = DISPLAY_HEIGHT - 1;
}

void	render_column(t_game *game, int column_x, t_ray *ray)
{
	t_render	r;

	init_renderer(game, &r, ray);
	if (ray->hit_type == 'P')
		render_wall_portal(game, column_x, &r, ray);
	else if (ray->hit_type == 'D')
		render_door(game, column_x, &r, ray);
	else if (ray->hit_type == 'i')
		render_wall_shooted(game, column_x, &r, ray);
	else if (ray->hit_type == 'd')
		render_door_shooted(game, column_x, &r, ray);
	else
		render_wall(game, column_x, &r, ray);
	render_floor_and_ceiling(game, column_x, &r);
}
