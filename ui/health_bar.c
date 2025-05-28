/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:16:09 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 18:45:38 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_health_bar(t_game *game)
{
	game->health_bar.x = 50;
	game->health_bar.y = 50;
	game->health_bar.width = 500;
	game->health_bar.height = 40;
	game->health_bar.border = 5;
	game->health_bar.border_color = 0x000000;
	game->health_bar.empty_color = 0x555555;
	game->health_bar.health_color = 0xFF0000;
}

void	draw_health_bar_border(t_game *game)
{
	t_health_bar	*life_bar;
	char			*pixel;
	int				x;
	int				y;

	life_bar = &game->health_bar;
	y = life_bar->y;
	while (y < life_bar->y + life_bar->height)
	{
		x = life_bar->x;
		while (x < life_bar->x + life_bar->width)
		{
			pixel = game->screen.addr + (y * game->screen.line_length + x
					* (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = life_bar->border_color;
			x++;
		}
		y++;
	}
}

void	draw_health_bar_background(t_game *game)
{
	t_health_bar	*life_bar;
	char			*pixel;
	int				x;
	int				y;

	life_bar = &game->health_bar;
	y = life_bar->y + life_bar->border;
	while (y < life_bar->y + life_bar->height - life_bar->border)
	{
		x = life_bar->x + life_bar->border;
		while (x < life_bar->x + life_bar->width - life_bar->border)
		{
			pixel = game->screen.addr + (y * game->screen.line_length + x
					* (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = life_bar->empty_color;
			x++;
		}
		y++;
	}
}

void	draw_health_bar(t_game *game)
{
	draw_health_bar_border(game);
	draw_health_bar_background(game);
	draw_health_bar_fill(game);
}
