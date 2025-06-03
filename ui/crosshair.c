/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:53 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:54 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	draw_vertical_line(t_game *game, int center_x, int center_y,
		int size)
{
	char			*pixel;
	int				i;
	unsigned int	color;

	color = 0x000000;
	i = -size;
	while (i <= size)
	{
		if (center_y + i >= 0 && center_y + i < DISPLAY_HEIGHT)
		{
			pixel = game->screen.addr + ((center_y + i)
					* game->screen.line_length + center_x
					* (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
		}
		i++;
	}
}

static void	draw_horizontal_line(t_game *game, int center_x, int center_y,
		int size)
{
	char			*pixel;
	int				i;
	unsigned int	color;

	color = 0x000000;
	i = -size;
	while (i <= size)
	{
		if (center_x + i >= 0 && center_x + i < DISPLAY_WIDTH)
		{
			pixel = game->screen.addr + (center_y * game->screen.line_length
					+ (center_x + i) * (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
		}
		i++;
	}
}

void	draw_crosshair(t_game *game)
{
	int	center_x;
	int	center_y;
	int	size;

	center_x = DISPLAY_WIDTH / 2;
	center_y = DISPLAY_HEIGHT / 2;
	size = 5;
	draw_vertical_line(game, center_x, center_y, size);
	draw_horizontal_line(game, center_x, center_y, size);
}
