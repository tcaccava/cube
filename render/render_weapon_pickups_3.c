/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon_pickups_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:17 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:18 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	set_pickup_pixel_color(t_game *game, int coords[2], unsigned int color)
{
	char	*dst;

	dst = game->screen.addr + coords[1] * game->screen.line_length
		+ coords[0] * (game->screen.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	calculate_weapon_transform(t_game *game, t_weapon_pickup *weapon,
		t_render *render)
{
	double	dx;
	double	dy;
	double	inv_det;

	dx = weapon->x - game->player.x;
	dy = weapon->y - game->player.y;
	inv_det = 1.0f / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	render->floor_x = inv_det * (game->player.dir_y * dx
			- game->player.dir_x * dy);
	render->floor_y = inv_det * (-game->player.plane_y * dx
			+ game->player.plane_x * dy);
}

void	calculate_weapon_screen_pos(t_game *game, t_render *render)
{
	double	distance_to_projection_plane;
	double	corrected_dist;
	double	weapon_height;

	weapon_height = TILE_SIZE * 0.1;
	render->x = (int)((DISPLAY_WIDTH / 2) * (1 + render->floor_x
				/ render->floor_y));
	distance_to_projection_plane = (DISPLAY_WIDTH / 2.0)
		/ tan(game->player.fov / 2.0);
	corrected_dist = fmax(render->floor_y, 0.1);
	render->sprite_size = (int)((weapon_height / corrected_dist)
			* distance_to_projection_plane);
	if (render->sprite_size > DISPLAY_HEIGHT * 2)
		render->sprite_size = DISPLAY_HEIGHT * 2;
	if (render->sprite_size < 1)
		render->sprite_size = 1;
}

void	setup_weapon_pickup_render(t_game *game, t_render *renderer)
{
	setup_enemy_render_params(game, renderer);
	renderer->draw_end += 400;
}

double	calculate_distance_to_weapon(t_game *game, t_weapon_pickup *weapon)
{
	double	dx;
	double	dy;

	dx = weapon->x - game->player.x;
	dy = weapon->y - game->player.y;
	return (sqrt(dx * dx + dy * dy));
}
