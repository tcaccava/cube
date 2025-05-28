/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_health_bar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:52:51 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 16:51:47 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	calculate_filled_width(t_game *game)
{
	t_health_bar	*life_bar;
	int				max_health;
	int				current_health;
	int				inner_width;
	int				filled_width;

	life_bar = &game->health_bar;
	max_health = 100;
	current_health = game->player.health - 50;
	if (current_health < 0)
		current_health = 0;
	if (current_health > max_health)
		current_health = max_health;
	inner_width = life_bar->width - 2 * life_bar->border;
	filled_width = (current_health * inner_width) / max_health;
	return (filled_width);
}

void	draw_health_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = game->screen.addr + (y * game->screen.line_length + x
			* (game->screen.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	draw_health_bar_fill(t_game *game)
{
	t_health_bar	*life_bar;
	int				filled_width;
	int				x;
	int				y;

	life_bar = &game->health_bar;
	filled_width = calculate_filled_width(game);
	y = life_bar->y + life_bar->border;
	while (y < life_bar->y + life_bar->height - life_bar->border)
	{
		x = life_bar->x + life_bar->border;
		while (x < life_bar->x + life_bar->border + filled_width)
		{
			draw_health_pixel(game, x, y, life_bar->health_color);
			x++;
		}
		y++;
	}
}
