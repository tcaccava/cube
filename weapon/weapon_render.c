/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:34 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:35 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_weapon(t_game *game)
{
	t_render	renderer;
	t_img		*weapon;

	if (game->map.north.ptr != NULL)
		return ;
	weapon = get_current_weapon_sprite(game);
	if (!weapon)
		return ;
	calculate_weapon_position(game, &renderer, weapon);
	update_weapon_animation(game);
	draw_weapon_sprite(game, &renderer, weapon);
}

t_img	*get_current_weapon_sprite(t_game *game)
{
	if (game->current_weapon == HEALGUN)
		return (get_healgun_sprite(game));
	else
		return (&game->weapons[game->current_weapon]
			[game->player.weapon.frame]);
}

t_img	*get_healgun_sprite(t_game *game)
{
	if (game->player.healgun_animating)
		return (&game->healgun_frames[game->player.healgun_anim_frame]);
	else if (game->player.healgun_ammo > 0)
		return (&game->healgun_frames[0]);
	else
		return (&game->healgun_frames[4]);
}

void	calculate_weapon_position(t_game *game, t_render *renderer,
		t_img *weapon)
{
	renderer->x = (DISPLAY_WIDTH - weapon->width) + 180;
	if (is_healgun_frame_2(game))
		renderer->x = (DISPLAY_WIDTH - weapon->width) + 100;
	renderer->y = (DISPLAY_HEIGHT - weapon->height) + 250 + game->pitch;
	if (is_healgun_frame_2(game))
		renderer->y += 600;
}

int	is_healgun_frame_2(t_game *game)
{
	if (game->current_weapon == HEALGUN)
		if (game->player.healgun_animating)
			if (game->player.healgun_anim_frame == 2)
				return (1);
	return (0);
}
