/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:41:22 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 14:46:48 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_ceiling(t_game *game, int column_x, t_render *renderer)
{
	int				y;
	unsigned int	ceiling_color;

	y = 0;
	ceiling_color = 0x777777;
	while (y < renderer->draw_start)
	{
		renderer->screen_pixel = game->screen.addr + (y
				* game->screen.line_length + column_x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = ceiling_color;
		y++;
	}
}

void	render_floor_section(t_game *game, int column_x, t_render *renderer)
{
	int				y;
	unsigned int	floor_color;

	y = renderer->draw_end + 1;
	floor_color = 0x444444;
	while (y < DISPLAY_HEIGHT)
	{
		renderer->screen_pixel = game->screen.addr + (y
				* game->screen.line_length + column_x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = floor_color;
		y++;
	}
}

void	render_floor_and_ceiling(t_game *game, int column_x, t_render *renderer)
{
	render_ceiling(game, column_x, renderer);
	render_floor_section(game, column_x, renderer);
}

void	render_sky(t_game *game, int column_x, t_render *renderer)
{
	int	screen_y;

	renderer->y = 0;
	screen_y = renderer->y - game->pitch;
	renderer->color = 0xb0a56b;
	while (renderer->y < renderer->draw_start)
	{
		renderer->screen_pixel = game->screen.addr + (screen_y
				* game->screen.line_length + column_x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = renderer->color;
		renderer->y++;
	}
}

void	render_floor(t_game *game, int column_x, t_render *renderer)
{
	int				y;
	unsigned int	floor_color;
	unsigned int	ceiling_color;

	floor_color = 0x444444;
	ceiling_color = 0x777777;
	y = 0;
	while (y < renderer->draw_start)
	{
		renderer->screen_pixel = game->screen.addr + (y
				* game->screen.line_length + column_x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = ceiling_color;
		y++;
	}
	y = renderer->draw_end + 1;
	while (y < DISPLAY_HEIGHT)
	{
		renderer->screen_pixel = game->screen.addr + (y
				* game->screen.line_length + column_x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)(renderer->screen_pixel) = floor_color;
		y++;
	}
}
