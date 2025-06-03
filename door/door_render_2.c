/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:46 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:47 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	render_damaged_pixel(t_game *game, t_render *renderer,
		int column_x, int texture_y)
{
	unsigned int	damaged_color;

	renderer->tex_addr = game->map.door_shooted_texture.addr
		+ (texture_y * game->map.door_shooted_texture.line_length
			+ renderer->tex_x * (game->map.door_shooted_texture
				.bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	apply_damage_effect(renderer->color, &damaged_color);
	renderer->screen_pixel = game->screen.addr
		+ (renderer->y * game->screen.line_length
			+ column_x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)renderer->screen_pixel = damaged_color;
}

void	render_shooted_door_column(t_game *game, t_render *renderer,
		int column_x)
{
	int		cy;
	double	h;
	int		texture_y;
	float	rel;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	h = renderer->wall_height;
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
		{
			rel = ((renderer->y - cy) / h) + 0.5f;
			texture_y = (int)(rel * TILE_SIZE);
			if (texture_y < 0)
				texture_y = 0;
			else if (texture_y >= TILE_SIZE)
				texture_y = TILE_SIZE - 1;
			render_damaged_pixel(game, renderer, column_x, texture_y);
		}
		renderer->y++;
	}
}

static void	calculate_open_door_texture(t_render *renderer, t_ray *ray)
{
	if (ray->hit_vertical)
	{
		renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
		if (cos(ray->radiant_angle) > 0)
			renderer->tex_x = TILE_SIZE - renderer->tex_x - 1;
	}
	else
	{
		renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
		if (sin(ray->radiant_angle) < 0)
			renderer->tex_x = TILE_SIZE - renderer->tex_x - 1;
	}
}

void	render_shooted_open_door(t_game *game, int column_x,
		t_render *renderer, t_ray *ray)
{
	double	cell_pos;
	double	frame_thickness;
	int		is_on_frame;

	calculate_open_door_texture(renderer, ray);
	cell_pos = (double)renderer->tex_x / TILE_SIZE;
	frame_thickness = 0.2;
	is_on_frame = (cell_pos < frame_thickness)
		|| (cell_pos > 1.0 - frame_thickness);
	if (!is_on_frame)
		return ;
	render_shooted_door_column(game, renderer, column_x);
}
