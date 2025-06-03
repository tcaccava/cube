/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:38 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:39 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	calculate_texture_y_from_position(int y, int cy, double h)
{
	float	rel;
	int		texture_y;

	rel = ((y - cy) / h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	return (texture_y);
}

void	set_wall_pixel_color(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = game->screen.addr + (y * game->screen.line_length
			+ x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	is_valid_screen_position(int x, int y)
{
	if (x < 0 || x >= DISPLAY_WIDTH)
		return (0);
	if (y < 0 || y >= DISPLAY_HEIGHT)
		return (0);
	return (1);
}

void	calculate_vertical_texture_x(t_render *renderer, t_ray *ray)
{
	renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
	if (cos(ray->radiant_angle) > 0)
		renderer->tex_x = TILE_SIZE - renderer->tex_x - 1;
}

void	calculate_horizontal_texture_x(t_render *renderer, t_ray *ray)
{
	renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
	if (sin(ray->radiant_angle) < 0)
		renderer->tex_x = TILE_SIZE - renderer->tex_x - 1;
}
