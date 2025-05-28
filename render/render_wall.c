/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:14:04 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 16:54:37 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_wall_portal(t_game *game, int column_x, t_render *renderer,
		t_ray *ray)
{
	int	cy;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	if (ray->hit_vertical)
		renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
	else
		renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
			render_wall_portal_pixel(game, column_x, renderer, cy);
		renderer->y++;
	}
}

void	render_wall_portal_pixel(t_game *game, int column_x, t_render *renderer,
		int cy)
{
	double	h;
	float	rel;
	int		texture_y;

	h = renderer->wall_height;
	rel = ((renderer->y - cy) / h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	renderer->tex_addr = game->map.wall_portal_texture.addr + (texture_y
			* game->map.wall_portal_texture.line_length + renderer->tex_x
			* (game->map.wall_portal_texture.bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->screen_pixel = game->screen.addr + (renderer->y
			* game->screen.line_length + column_x * (game->screen.bits_per_pixel
				/ 8));
	*(unsigned int *)renderer->screen_pixel = renderer->color;
}

void	render_wall_shooted(t_game *game, int column_x, t_render *renderer,
		t_ray *ray)
{
	int	cy;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	if (ray->hit_vertical)
		renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
	else
		renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
			render_wall_shooted_pixel(game, column_x, renderer, cy);
		renderer->y++;
	}
}

void	render_wall_shooted_pixel(t_game *game, int column_x,
		t_render *renderer, int cy)
{
	double	h;
	float	rel;
	int		texture_y;

	h = renderer->wall_height;
	rel = ((renderer->y - cy) / h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	renderer->tex_addr = game->map.wall_shooted_texture.addr + (texture_y
			* game->map.wall_shooted_texture.line_length + renderer->tex_x
			* (game->map.wall_shooted_texture.bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->screen_pixel = game->screen.addr + (renderer->y
			* game->screen.line_length + column_x * (game->screen.bits_per_pixel
				/ 8));
	*(unsigned int *)renderer->screen_pixel = renderer->color;
}

t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (game->map.north.ptr != NULL)
	{
		if (ray->hit_vertical)
		{
			if (cos(ray->radiant_angle) > 0)
				return (&game->map.east);
			else
				return (&game->map.west);
		}
		else
		{
			if (sin(ray->radiant_angle) > 0)
				return (&game->map.south);
			else
				return (&game->map.north);
		}
	}
	else
	{
		return (&game->map.wall_texture);
	}
}
