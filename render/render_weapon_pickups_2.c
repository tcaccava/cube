/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon_pickups_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:14 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:15 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_weapon_pickup_pixel(t_game *game, t_weapon_pixel_data *data)
{
	int				src_coords[2];
	unsigned int	color;
	int				screen_coords[2];

	calculate_pickup_src_coords(data, src_coords);
	color = get_pickup_pixel_color(data->sprite, src_coords);
	if (is_pickup_pixel_transparent(color))
		return ;
	screen_coords[0] = data->pos.x + data->i;
	screen_coords[1] = data->pos.y + data->j;
	if (is_valid_screen_coord(screen_coords))
		set_pickup_pixel_color(game, screen_coords, color);
}

void	calculate_pickup_src_coords(t_weapon_pixel_data *data,
		int src_coords[2])
{
	src_coords[0] = data->i * data->sprite->width / data->size;
	src_coords[1] = data->j * data->sprite->height / data->size;
	if (src_coords[0] < 0)
		src_coords[0] = 0;
	if (src_coords[0] >= data->sprite->width)
		src_coords[0] = data->sprite->width - 1;
	if (src_coords[1] < 0)
		src_coords[1] = 0;
	if (src_coords[1] >= data->sprite->height)
		src_coords[1] = data->sprite->height - 1;
}

unsigned int	get_pickup_pixel_color(t_img *sprite, int src_coords[2])
{
	char	*src;

	src = sprite->addr + src_coords[1] * sprite->line_length
		+ src_coords[0] * (sprite->bits_per_pixel / 8);
	return (*(unsigned int *)src);
}

int	is_pickup_pixel_transparent(unsigned int color)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	if (red < 10 && green < 10 && blue < 10)
		return (1);
	if (abs(red - 255) <= 2 && abs(green - 0) <= 2 && abs(blue - 0) <= 2)
		return (1);
	if (red >= 250 && green >= 160 && green <= 175)
		return (1);
	return (0);
}

int	is_valid_screen_coord(int coords[2])
{
	if (coords[0] < 0 || coords[0] >= DISPLAY_WIDTH)
		return (0);
	if (coords[1] < 0 || coords[1] >= DISPLAY_HEIGHT)
		return (0);
	return (1);
}
