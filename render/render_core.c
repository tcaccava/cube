/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:28:40 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 16:50:40 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_scene(t_game *game)
{
	int	col;

	col = 0;
	while (col < DISPLAY_WIDTH)
	{
		render_column(game, col, &game->rays[col]);
		col++;
	}
}

void	render_frame(t_game *game)
{
	int	col;

	col = 0;
	while (col < DISPLAY_WIDTH)
	{
		render_column(game, col, &game->rays[col]);
		col++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.ptr, 0, 0);
	render_weapon(game);
}

void	render_ui(t_game *game)
{
	render_weapon(game);
	draw_health_bar(game);
	minimap(game);
}

void	render_next_frame_enemies(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->num_enemies)
	{
		if (game->enemies[j].active)
			render_enemy(game, &game->enemies[j]);
		j++;
	}
}
