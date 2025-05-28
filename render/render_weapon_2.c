/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:49:32 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 17:08:43 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	update_raygun_state(t_game *game)
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

void	update_weapon_animation(t_game *game)
{
	if (!game->player.weapon.is_firing)
		return ;
	game->player.weapon.frame_delay--;
	if (game->player.weapon.frame_delay <= 0 && game->current_weapon == RAYGUN)
		update_raygun_state(game);
}

void	draw_weapon_pixel(t_game *game, t_img *weapon, t_render *renderer,
		t_point tex)
{
	char	*dst;

	renderer->tex_addr = weapon->addr + (tex.y * weapon->line_length + tex.x
			* (weapon->bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->red = (renderer->color >> 16) & 0xFF;
	renderer->green = (renderer->color >> 8) & 0xFF;
	renderer->blue = renderer->color & 0xFF;
	if (!(renderer->red < 10 && renderer->green < 10 && renderer->blue < 10))
	{
		dst = game->screen.addr + ((renderer->y + tex.y)
				* game->screen.line_length + (renderer->x + tex.x)
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)dst = renderer->color;
	}
}

static void	draw_weapon_texture(t_game *game, t_img *weapon, t_render *r)
{
	t_point	tex;

	while (r->tex_y < weapon->height)
	{
		if (r->y + r->tex_y >= 0 && r->y + r->tex_y < DISPLAY_HEIGHT)
		{
			r->tex_x = 0;
			while (r->tex_x < weapon->width)
			{
				if (r->x + r->tex_x >= 0 && r->x + r->tex_x < DISPLAY_WIDTH)
				{
					tex.x = r->tex_x;
					tex.y = r->tex_y;
					draw_weapon_pixel(game, weapon, r, tex);
				}
				r->tex_x++;
			}
		}
		r->tex_y++;
	}
}

void	render_weapon(t_game *game)
{
	t_render	renderer;
	t_img		*weapon;

	if (game->map.north.ptr != NULL)
		return ;
	weapon = &game->weapons[game->current_weapon][game->player.weapon.frame];
	renderer.x = (DISPLAY_WIDTH - weapon->width) + 180;
	renderer.y = (DISPLAY_HEIGHT - weapon->height) + 250 + game->pitch;
	update_weapon_animation(game);
	renderer.tex_y = 0;
	draw_weapon_texture(game, weapon, &renderer);
}
