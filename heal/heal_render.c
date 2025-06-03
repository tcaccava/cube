/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heal_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:21:10 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:21:11 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_healgun_animation(t_game *game)
{
	t_img	*arm_sprite;
	int		arm_x;
	int		arm_y;

	arm_sprite = &game->map.arm_1;
	arm_x = 50;
	arm_y = DISPLAY_HEIGHT - arm_sprite->height - 50;
	draw_arm_sprite(game, arm_sprite, arm_x, arm_y);
}

void	draw_heal_pixel(t_game *game, t_img *sprite, int x, int y)
{
	t_heal_coords	coords;
	char			*src;
	char			*dst;
	unsigned int	color;

	coords.x = x;
	coords.y = y;
	coords.px = x % sprite->width;
	coords.py = y % sprite->height;
	if (!is_pixel_in_bounds(coords.x, coords.y))
		return ;
	src = get_sprite_pixel(sprite, coords.px, coords.py);
	color = *(unsigned int *)src;
	if (is_transparent_pixel(color))
		return ;
	dst = get_screen_pixel(game, coords.x, coords.y);
	*(unsigned int *)dst = color;
}

void	draw_arm_row_at(t_game *game, t_img *sprite, int x, int y)
{
	int	pixel_x;

	pixel_x = 0;
	while (pixel_x < sprite->width)
	{
		draw_heal_pixel(game, sprite, x + pixel_x, y);
		pixel_x++;
	}
}

void	draw_arm_sprite(t_game *game, t_img *sprite, int x, int y)
{
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < sprite->height)
	{
		draw_arm_row_at(game, sprite, x, y + pixel_y);
		pixel_y++;
	}
}

int	is_transparent_pixel(unsigned int color)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	if (red < 10 && green < 10 && blue < 10)
		return (1);
	return (0);
}
