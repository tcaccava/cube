/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:09 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:13 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_ceiling(t_game *game, int column_x, t_render *renderer)
{
	int				y;
	unsigned int	ceiling_color;

	y = 0;
	ceiling_color = 0xc8b06e;
	while (y < renderer->draw_start)
	{
		renderer->screen_pixel = game->screen.addr + (y * game->screen
				.line_length + column_x * (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = ceiling_color;
		y++;
	}
}

void	render_floor_section(t_game *game, int column_x, t_render *renderer)
{
	int				y;
	unsigned int	floor_color;

	y = renderer->draw_end + 1;
	floor_color = 0x394156;
	while (y < DISPLAY_HEIGHT)
	{
		renderer->screen_pixel = game->screen.addr + (y * game->screen
				.line_length + column_x * (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = floor_color;
		y++;
	}
}

void	render_floor_and_ceiling(t_game *game, int column_x, t_render *renderer)
{
	render_ceiling(game, column_x, renderer);
	render_floor_section(game, column_x, renderer);
}

static void	render_door_shooted_pixel(t_game *game, t_render *renderer,
		int column_x)
{
	int		texture_y;
	float	rel;
	int		cy;
	double	h;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	h = renderer->wall_height;
	rel = ((renderer->y - cy) / h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	renderer->tex_addr = game->map.door_shooted_texture.addr
		+ (texture_y * game->map.door_shooted_texture.line_length
			+ renderer->tex_x * (game->map.door_shooted_texture
				.bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->screen_pixel = game->screen.addr
		+ (renderer->y * game->screen.line_length
			+ column_x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)renderer->screen_pixel = renderer->color;
}

void	render_door_shooted(t_game *game, int column_x, t_render *renderer,
		t_ray *ray)
{
	if (ray->hit_vertical)
		renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
	else
		renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
			render_door_shooted_pixel(game, renderer, column_x);
		renderer->y++;
	}
}
