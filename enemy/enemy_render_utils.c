/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:21 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:22 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_enemy_occlusion(t_game *game, t_render *render)
{
	int	sprite_start_pixel;
	int	sprite_end_pixel;
	int	sample_count;
	int	col;
	int	i;

	calculate_sprite_bounds(render, &sprite_start_pixel, &sprite_end_pixel);
	sample_count = 0;
	i = 0;
	while (i < 5)
	{
		col = sprite_start_pixel
			+ i * (sprite_end_pixel - sprite_start_pixel) / 4;
		if (render->floor_y < game->depth_buffer[col])
			sample_count++;
		i++;
	}
	return (sample_count > 0);
}

void	setup_enemy_render_params(t_game *game, t_render *render)
{
	int	y_offset;

	y_offset = 55;
	render->draw_start = render->x - render->sprite_size / 2;
	render->draw_end = (DISPLAY_HEIGHT - render->sprite_size) / 2
		+ game->pitch + y_offset;
}

void	calculate_enemy_transform(t_game *game, t_enemy *enemy,
			t_render *render)
{
	double	dx;
	double	dy;
	double	inv_det;

	dx = enemy->x - game->player.x;
	dy = enemy->y - game->player.y;
	inv_det = 1.0f / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	render->floor_x = inv_det * (game->player.dir_y * dx
			- game->player.dir_x * dy);
	render->floor_y = inv_det * (-game->player.plane_y * dx
			+ game->player.plane_x * dy);
}

void	calculate_enemy_screen_pos(t_game *game, t_render *render)
{
	double	distance_to_projection_plane;
	double	corrected_dist;
	double	enemy_height;

	render->x = (int)((DISPLAY_WIDTH / 2) * (1 + render->floor_x
				/ render->floor_y));
	distance_to_projection_plane = (DISPLAY_WIDTH / 2.0)
		/ tan(game->player.fov / 2.0);
	corrected_dist = fmax(render->floor_y, 0.1);
	enemy_height = TILE_SIZE * 1.4;
	render->sprite_size = (int)((enemy_height / corrected_dist)
			* distance_to_projection_plane);
	if (render->sprite_size > DISPLAY_HEIGHT * 2)
		render->sprite_size = DISPLAY_HEIGHT * 2;
	if (render->sprite_size < 1)
		render->sprite_size = 1;
}
