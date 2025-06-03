/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_pickup_render_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:07 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:08 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	setup_weapon_pickup_render(t_game *game, t_render *renderer)
{
	setup_enemy_render_params(game, renderer);
	renderer->draw_end += 400;
}

void	draw_weapon_pickup_sprite(t_game *game, t_img *sprite, t_point pos,
		int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		draw_weapon_pickup_row(game, sprite, pos, size);
		i++;
	}
}

static void	calculate_pixel_coords(t_pixel_data *pixel, t_img *sprite,
		t_point pos, int size)
{
	if (pixel->src_x >= sprite->width)
		pixel->src_x = sprite->width - 1;
	if (pixel->src_y >= sprite->height)
		pixel->src_y = sprite->height - 1;
	pixel->x = pos.x + (pixel->src_x * size / sprite->width);
	pixel->y = pos.y + (pixel->src_y * size / sprite->height);
}

static void	get_pixel_color(t_pixel_data *pixel, t_img *sprite)
{
	char	*src;

	src = sprite->addr + pixel->src_y * sprite->line_length
		+ pixel->src_x * (sprite->bits_per_pixel / 8);
	pixel->color = *(unsigned int *)src;
}

static void	draw_single_pixel(t_game *game, t_pixel_data *pixel)
{
	char	*dst;

	if (pixel->x >= 0 && pixel->x < DISPLAY_WIDTH
		&& pixel->y >= 0 && pixel->y < DISPLAY_HEIGHT)
	{
		dst = game->screen.addr + pixel->y * game->screen.line_length
			+ pixel->x * (game->screen.bits_per_pixel / 8);
		*(unsigned int *)dst = pixel->color;
	}
}
