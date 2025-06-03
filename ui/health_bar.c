/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:55 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:56 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_health_bar(t_game *game)
{
	t_health_bar	*life_bar;

	life_bar = &game->health_bar;
	life_bar->x = 50;
	life_bar->y = 50;
	life_bar->width = 500;
	life_bar->height = 40;
	life_bar->border = 5;
	life_bar->border_color = 0x000000;
	life_bar->empty_color = 0x555555;
	life_bar->health_color = 0xFF0000;
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
			pixel = game->screen.addr + (y * game->screen.line_length
					+ x * (game->screen.bits_per_pixel / 8));
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
			pixel = game->screen.addr + (y * game->screen.line_length
					+ x * (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = life_bar->empty_color;
			x++;
		}
		y++;
	}
}

static void	calculate_health_dimensions(t_game *game, int *inner_width,
		int *filled_width)
{
	t_health_bar	*life_bar;
	int				current_health;
	int				max_health;

	life_bar = &game->health_bar;
	max_health = 100;
	current_health = game->player.health;
	if (current_health < 0)
		current_health = 0;
	if (current_health > max_health)
		current_health = max_health;
	*inner_width = life_bar->width - 2 * life_bar->border;
	*filled_width = (current_health * (*inner_width)) / max_health;
}

void	draw_health_bar_fill(t_game *game)
{
	t_health_bar	*life_bar;
	int				dimensions[2];
	int				x;
	int				y;
	char			*pixel;

	life_bar = &game->health_bar;
	calculate_health_dimensions(game, &dimensions[0], &dimensions[1]);
	y = life_bar->y + life_bar->border;
	while (y < life_bar->y + life_bar->height - life_bar->border)
	{
		x = life_bar->x + life_bar->border;
		while (x < life_bar->x + life_bar->border + dimensions[1])
		{
			pixel = game->screen.addr + (y * game->screen.line_length
					+ x * (game->screen.bits_per_pixel / 8));
			*(unsigned int *)pixel = life_bar->health_color;
			x++;
		}
		y++;
	}
}
