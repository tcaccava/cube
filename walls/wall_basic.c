/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:29 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:30 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	calculate_wall_texture_x(t_render *renderer, t_ray *ray)
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

static void	calculate_wall_texture_y(t_render *renderer, int cy, double h)
{
	float	rel;
	int		texture_y;

	rel = ((renderer->y - cy) / h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	renderer->tex_y = texture_y;
}

static void	render_wall_pixel(t_game *game, t_img *texture,
				t_render *renderer, int column_x)
{
	renderer->tex_addr = texture->addr + (renderer->tex_y * texture->line_length
			+ renderer->tex_x * (texture->bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->screen_pixel = game->screen.addr
		+ (renderer->y * game->screen.line_length
			+ column_x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)renderer->screen_pixel = renderer->color;
}

static void	render_wall_column(t_game *game, t_img *texture,
		t_render *renderer, int column_x)
{
	int		cy;
	double	h;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	h = renderer->wall_height;
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
		{
			calculate_wall_texture_y(renderer, cy, h);
			render_wall_pixel(game, texture, renderer, column_x);
		}
		renderer->y++;
	}
}

void	render_wall(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
	t_img	*current_texture;

	current_texture = get_wall_texture(game, ray);
	calculate_wall_texture_x(renderer, ray);
	render_wall_column(game, current_texture, renderer, column_x);
}
