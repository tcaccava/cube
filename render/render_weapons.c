/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:23 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:24 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	handle_frame_delay_expired(t_game *game)
{
	if (game->current_weapon == RAYGUN)
	{
		if (game->player.weapon.current_state == WEAPON_PREFIRE)
		{
			game->player.weapon.current_state = WEAPON_FIRE;
			game->player.weapon.frame = 2;
			game->player.weapon.frame_delay = 2;
		}
		else if (game->player.weapon.current_state == WEAPON_FIRE)
		{
			game->player.weapon.current_state = WEAPON_POSTFIRE;
			game->player.weapon.frame = 1;
			game->player.weapon.frame_delay = 2;
		}
		else if (game->player.weapon.current_state == WEAPON_POSTFIRE)
		{
			game->player.weapon.current_state = WEAPON_NEUTRE;
			game->player.weapon.frame = 0;
			game->player.weapon.is_firing = 0;
		}
	}
}

void	update_weapon_animation(t_game *game)
{
	if (game->current_weapon == HANDS)
		return ;
	if (game->player.weapon.is_firing)
	{
		game->player.weapon.frame_delay--;
		if (game->player.weapon.frame_delay <= 0)
			handle_frame_delay_expired(game);
	}
}

void	draw_weapon_pixel_render(t_game *game, t_img *weapon,
		t_render *renderer)
{
	char	*dst;

	renderer->tex_addr = weapon->addr + (renderer->tex_y * weapon->line_length
			+ renderer->tex_x * (weapon->bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->red = (renderer->color >> 16) & 0xFF;
	renderer->green = (renderer->color >> 8) & 0xFF;
	renderer->blue = renderer->color & 0xFF;
	if (!(renderer->red < 10 && renderer->green < 10 && renderer->blue < 10))
	{
		dst = game->screen.addr + ((renderer->y + renderer->tex_y)
				* game->screen.line_length + (renderer->x + renderer->tex_x)
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)dst = renderer->color;
	}
}
