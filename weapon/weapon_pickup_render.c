/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_pickup_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:40 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:58 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_weapon_pickup(t_game *game, t_weapon_pickup *weapon)
{
	t_render	renderer;
	int			is_visible;

	if (!weapon->active)
		return ;
	if (should_skip_weapon_render(game, weapon))
		return ;
	calculate_weapon_transform(game, weapon, &renderer);
	if (renderer.floor_y <= 0.2f)
		return ;
	calculate_weapon_screen_pos(game, &renderer);
	if (renderer.x < 0 || renderer.x >= DISPLAY_WIDTH)
		return ;
	is_visible = check_enemy_occlusion(game, &renderer);
	if (!is_visible)
		return ;
	setup_weapon_pickup_render(game, &renderer);
	draw_weapon_pickup_sprite(game, &weapon->sprite,
		(t_point){renderer.draw_start, renderer.draw_end},
		renderer.sprite_size);
}

int	should_skip_weapon_render(t_game *game, t_weapon_pickup *weapon)
{
	if (weapon->weapon_type == HEALGUN)
		return (setup_healgun_pickup_sprite(game, weapon));
	else if (game->player.has_weapon[weapon->weapon_type])
		return (1);
	return (0);
}

int	setup_healgun_pickup_sprite(t_game *game, t_weapon_pickup *weapon)
{
	if (game->player.has_weapon[HEALGUN])
	{
		if (!load_weapon_pickup_sprite(game, weapon,
				"./texture/w_heal_pickup.xpm"))
			printf("Warning: syringe_pickup.xpm not found\n");
	}
	else
	{
		if (!weapon->sprite.ptr)
			load_weapon_pickup_sprite(game, weapon,
				"./texture/w_healgun_pickup.xpm");
	}
	return (0);
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
