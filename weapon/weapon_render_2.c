/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_render_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:36 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:37 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_weapon_animation(t_game *game)
{
	if (game->current_weapon == HANDS)
		return ;
	if (game->player.weapon.is_firing)
		process_weapon_animation(game);
	if (game->player.healgun_animating && game->player.healgun_anim_timer > 0)
		process_healgun_animation(game);
}

void	draw_weapon_sprite(t_game *game, t_render *renderer, t_img *weapon)
{
	renderer->tex_y = 0;
	while (renderer->tex_y < weapon->height)
	{
		if (renderer->y + renderer->tex_y >= 0 && renderer->y
			+ renderer->tex_y < DISPLAY_HEIGHT)
			draw_weapon_row(game, renderer, weapon);
		renderer->tex_y++;
	}
}

void	draw_weapon_row(t_game *game, t_render *renderer, t_img *weapon)
{
	renderer->tex_x = 0;
	while (renderer->tex_x < weapon->width)
	{
		if (renderer->x + renderer->tex_x >= 0 && renderer
			->x + renderer->tex_x < DISPLAY_WIDTH)
			draw_weapon_pixel_at_coords(game, weapon, renderer);
		renderer->tex_x++;
	}
}

static void	calculate_pixel_color(t_img *weapon, t_render *renderer)
{
	renderer->tex_addr = weapon->addr + (renderer->tex_y * weapon
			->line_length + renderer->tex_x * (weapon->bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->red = (renderer->color >> 16) & 0xFF;
	renderer->green = (renderer->color >> 8) & 0xFF;
	renderer->blue = renderer->color & 0xFF;
}

void	draw_weapon_pixel_at_coords(t_game *game, t_img *weapon,
		t_render *renderer)
{
	char	*dst;

	calculate_pixel_color(weapon, renderer);
	if (!(renderer->red < 10 && renderer->green < 10
			&& renderer->blue < 10))
	{
		dst = game->screen.addr + ((renderer->y + renderer->tex_y)
				* game->screen.line_length + (renderer->x
					+ renderer->tex_x) * (game->screen.bits_per_pixel / 8));
		*(unsigned int *)dst = renderer->color;
	}
}
