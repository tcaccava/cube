/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_laser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:21:00 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:21:04 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_horizontal_line(t_game *game, int column, int y)
{
	int		x_offset;
	int		x;
	char	*pixel;

	if (y < 0 || y >= DISPLAY_HEIGHT)
		return ;
	x_offset = -15;
	while (x_offset <= 15)
	{
		x = column + x_offset;
		if (x >= 0 && x < DISPLAY_WIDTH)
		{
			pixel = game->screen.addr + (y * game->screen.line_length
					+ x * (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = 0xFF0000;
		}
		x_offset++;
	}
}

void	render_laser_overlays(t_game *game)
{
	int	col;

	col = 0;
	while (col < DISPLAY_WIDTH)
	{
		if (ray_crosses_laser(game, game->rays[col].radiant_angle))
			draw_laser_line_on_column(game, col);
		col++;
	}
}

void	draw_laser_line_on_column(t_game *game, int column)
{
	int	center_y;
	int	line_positions[5];
	int	line;

	center_y = DISPLAY_HEIGHT / 2 + game->pitch;
	init_laser_positions(line_positions, center_y);
	line = 0;
	while (line < 5)
	{
		draw_horizontal_line(game, column, line_positions[line]);
		line++;
	}
}
