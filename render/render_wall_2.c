/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:25:27 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 16:51:52 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	render_wall_pixel(t_game *game, t_render *r, t_img *tex, int col_x)
{
	float	rel;
	int		texture_y;
	int		cy;
	double	wall_h;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	wall_h = r->wall_height;
	rel = ((r->y - cy) / wall_h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	r->tex_addr = tex->addr + (texture_y * tex->line_length + r->tex_x
			* (tex->bits_per_pixel / 8));
	r->color = *(unsigned int *)r->tex_addr;
	r->screen_pixel = game->screen.addr + (r->y * game->screen.line_length
			+ col_x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)r->screen_pixel = r->color;
}

void	render_wall(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
	t_img	*texture;

	texture = get_wall_texture(game, ray);
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
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
			render_wall_pixel(game, renderer, texture, column_x);
		renderer->y++;
	}
}
