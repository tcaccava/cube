/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:05:01 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 15:41:15 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	init_weapon_render(t_game *game, t_render *r, t_img **weapon)
{
	*weapon = &game->weapons[game->current_weapon][game->player.weapon.frame];
	r->x = (DISPLAY_WIDTH - (*weapon)->width) + 180;
	r->y = (DISPLAY_HEIGHT - (*weapon)->height) + 250 + game->pitch;
}

static void	update_weapon_state(t_game *game)
{
	if (!game->player.weapon.is_firing)
		return ;
	game->player.weapon.frame_delay--;
	if (game->player.weapon.frame_delay > 0)
		return ;
	if (game->current_weapon != RAYGUN)
		return ;
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

static void	draw_weapon_texture(t_game *game, t_render *r, t_img *weapon)
{
	r->tex_y = 0;
	while (r->tex_y < weapon->height)
	{
		if (r->y + r->tex_y >= 0 && r->y + r->tex_y < DISPLAY_HEIGHT)
			draw_weapon_row(game, r, weapon);
		r->tex_y++;
	}
}

static void	draw_weapon_row(t_game *game, t_render *r, t_img *weapon)
{
	char	*dst;

	r->tex_x = 0;
	while (r->tex_x < weapon->width)
	{
		if (r->x + r->tex_x >= 0 && r->x + r->tex_x < DISPLAY_WIDTH)
		{
			r->tex_addr = weapon->addr + (r->tex_y * weapon->line_length
					+ r->tex_x * (weapon->bits_per_pixel / 8));
			r->color = *(unsigned int *)r->tex_addr;
			r->red = (r->color >> 16) & 0xFF;
			r->green = (r->color >> 8) & 0xFF;
			r->blue = r->color & 0xFF;
			if (!(r->red < 10 && r->green < 10 && r->blue < 10))
			{
				dst = game->screen.addr + ((r->y + r->tex_y)
						* game->screen.line_length + (r->x + r->tex_x)
						* (game->screen.bits_per_pixel / 8));
				*(unsigned int *)dst = r->color;
			}
		}
		r->tex_x++;
	}
}

void	render_weapon(t_game *game)
{
	t_render	renderer;
	t_img		*weapon;

	if (game->map.north.ptr != NULL)
		return ;
	init_weapon_render(game, &renderer, &weapon);
	update_weapon_state(game);
	draw_weapon_texture(game, &renderer, weapon);
}
