/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapons_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:19 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 17:03:26 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_img	*get_weapon_sprite(t_game *game)
{
	if (game->current_weapon == HEALGUN)
	{
		if (game->player.healgun_animating)
		{
			return (&game->healgun_frames[game->player.healgun_anim_frame]);
		}
		else
		{
			if (game->player.healgun_ammo > 0)
				return (&game->healgun_frames[0]);
			else
				return (&game->healgun_frames[4]);
		}
	}
	else
		return (&game->weapons[game->current_weapon]
			[game->player.weapon.frame]);
}

static void	set_weapon_position(t_game *game, t_render *renderer, t_img *weapon)
{
	renderer->x = (DISPLAY_WIDTH - weapon->width) + 180;
	if (game->current_weapon == HEALGUN && game->player.healgun_animating
		&& game->player.healgun_anim_frame == 2)
	{
		renderer->x = (DISPLAY_WIDTH - weapon->width) + 100;
		renderer->y = (DISPLAY_HEIGHT - weapon->height) + 250
			+ game->pitch + 600;
	}
	else
		renderer->y = (DISPLAY_HEIGHT - weapon->height) + 250 + game->pitch;
}

static void	render_weapon_pixels(t_game *game, t_img *weapon,
		t_render *renderer)
{
	renderer->tex_y = 0;
	while (renderer->tex_y < weapon->height)
	{
		if (renderer->y + renderer->tex_y >= 0 && renderer->y
			+ renderer->tex_y < DISPLAY_HEIGHT)
		{
			renderer->tex_x = 0;
			while (renderer->tex_x < weapon->width)
			{
				if (renderer->x + renderer->tex_x >= 0
					&& renderer->x + renderer->tex_x < DISPLAY_WIDTH)
				{
					draw_weapon_pixel_render(game, weapon, renderer);
				}
				renderer->tex_x++;
			}
		}
		renderer->tex_y++;
	}
}

void	render_weapon(t_game *game)
{
	t_render	renderer;
	t_img		*weapon;

	weapon = get_weapon_sprite(game);
	set_weapon_position(game, &renderer, weapon);
	update_weapon_animation(game);
	render_weapon_pixels(game, weapon, &renderer);
}
