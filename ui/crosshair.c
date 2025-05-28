/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:15:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 18:29:03 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	draw_vertical_pixel(t_game *game, int center_x, int center_y,
		unsigned int color)
{
	char	*pixel;

	if (center_y >= 0 && center_y < DISPLAY_HEIGHT)
	{
		pixel = game->screen.addr + (center_y * game->screen.line_length
				+ center_x * (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

static void	draw_horizontal_pixel(t_game *game, int center_x, int center_y,
		unsigned int color)
{
	char	*pixel;

	if (center_x >= 0 && center_x < DISPLAY_WIDTH)
	{
		pixel = game->screen.addr + (center_y * game->screen.line_length
				+ center_x * (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

void	draw_crosshair_line(t_game *game, t_crosshair_params *params,
		int is_vertical)
{
	int	i;

	i = -params->size;
	while (i <= params->size)
	{
		if (is_vertical)
		{
			draw_vertical_pixel(game, params->center_x, params->center_y + i,
				params->color);
		}
		else
		{
			draw_horizontal_pixel(game, params->center_x + i, params->center_y,
				params->color);
		}
		i++;
	}
}

void	draw_crosshair(t_game *game)
{
	t_crosshair_params	params;

	params.center_x = DISPLAY_WIDTH / 2;
	params.center_y = DISPLAY_HEIGHT / 2;
	params.size = 5;
	params.color = 0xFF0000;
	draw_crosshair_line(game, &params, 1);
	draw_crosshair_line(game, &params, 0);
}
