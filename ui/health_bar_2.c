/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:19:28 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 18:44:17 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	draw_health_bar_row(t_game *game, int y, int filled_width)
{
	t_health_bar	*life_bar;
	char			*pixel;
	int				x;

	life_bar = &game->health_bar;
	x = life_bar->x + life_bar->border;
	while (x < life_bar->x + life_bar->border + filled_width)
	{
		pixel = game->screen.addr + (y * game->screen.line_length + x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = life_bar->health_color;
		x++;
	}
}

void	draw_health_bar_fill(t_game *game)
{
	t_health_bar	*life_bar;
	int				current_health;
	int				inner_width;
	int				filled_width;
	int				y;

	life_bar = &game->health_bar;
	current_health = game->player.health - 50;
	if (current_health < 0)
		current_health = 0;
	if (current_health > 100)
		current_health = 100;
	inner_width = life_bar->width - 2 * life_bar->border;
	filled_width = (current_health * inner_width) / 100;
	y = life_bar->y + life_bar->border;
	while (y < life_bar->y + life_bar->height - life_bar->border)
	{
		draw_health_bar_row(game, y, filled_width);
		y++;
	}
}
