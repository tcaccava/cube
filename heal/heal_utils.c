/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heal_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:21:17 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 17:01:40 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_pixel_in_bounds(int x, int y)
{
	if (x < 0 || x >= DISPLAY_WIDTH)
		return (0);
	if (y < 0 || y >= DISPLAY_HEIGHT)
		return (0);
	return (1);
}

char	*get_sprite_pixel(t_img *sprite, int x, int y)
{
	char	*pixel;

	pixel = sprite->addr + (y * sprite->line_length
			+ x * (sprite->bits_per_pixel / 8));
	return (pixel);
}

char	*get_screen_pixel(t_game *game, int x, int y)
{
	char	*pixel;

	pixel = game->screen.addr + (y * game->screen.line_length
			+ x * (game->screen.bits_per_pixel / 8));
	return (pixel);
}

void	init_healgun_animation(t_game *game)
{
	game->player.healgun_animating = 1;
	game->player.healgun_anim_frame = 0;
	game->player.healgun_anim_timer = 10;
	game->player.healgun_heal_applied = 0;
}

int	is_healgun_ready(t_game *game)
{
	if (!game->player.has_weapon[HEALGUN])
		return (0);
	if (game->player.healgun_ammo <= 0)
		return (0);
	if (!game->player.healgun_is_loaded)
		return (0);
	return (1);
}
