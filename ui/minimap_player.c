/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:07 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:17:08 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	draw_fov_pixel(t_game *game, double angle, int centers[2], int i)
{
	t_minimap	*mini_map;
	char		*pixel;
	int			coords[2];

	mini_map = &game->minimap;
	coords[0] = centers[0] + cos(angle) * i;
	coords[1] = centers[1] + sin(angle) * i;
	if (coords[0] >= mini_map->x + mini_map->border
		&& coords[0] < mini_map->x + mini_map->size - mini_map->border
		&& coords[1] >= mini_map->y + mini_map->border
		&& coords[1] < mini_map->y + mini_map->size - mini_map->border)
	{
		pixel = game->screen.addr + (coords[1] * game->screen.line_length
				+ coords[0] * (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = mini_map->player_color;
	}
}

void	draw_minimap_cone(t_game *game)
{
	t_minimap	*mini_map;
	int			centers[2];
	double		angles[4];
	int			i;

	mini_map = &game->minimap;
	centers[0] = mini_map->x + mini_map->size / 2;
	centers[1] = mini_map->y + mini_map->size / 2;
	angles[0] = M_PI / 2;
	angles[1] = game->player.angle - angles[0] / 2;
	angles[2] = game->player.angle + angles[0] / 2;
	angles[3] = 0.01;
	while (angles[1] <= angles[2])
	{
		i = 0;
		while (i < 45)
		{
			draw_fov_pixel(game, angles[1], centers, i);
			i++;
		}
		angles[1] += angles[3];
	}
}

static void	draw_circle_row(t_game *game, t_minimap *mini_map, int coords[4])
{
	char	*pixel;
	int		px;

	px = -coords[3];
	while (px <= coords[3])
	{
		if (px * px + coords[2] * coords[2] <= coords[3] * coords[3])
		{
			if (coords[0] + px >= mini_map->x + mini_map->border
				&& coords[0] + px < mini_map->x + mini_map->size
				- mini_map->border && coords[1] + coords[2]
				>= mini_map->y + mini_map->border && coords[1]
				+ coords[2] < mini_map->y + mini_map->size
				- mini_map->border)
			{
				pixel = game->screen.addr + ((coords[1] + coords[2])
						* game->screen.line_length + (coords[0] + px)
						* (game->screen.bits_per_pixel / 8));
				*(unsigned int *)pixel = mini_map->player_color;
			}
		}
		px++;
	}
}

void	draw_player_circle(t_game *game, int center_x, int center_y)
{
	t_minimap	*mini_map;
	int			coords[4];

	mini_map = &game->minimap;
	coords[0] = center_x;
	coords[1] = center_y;
	coords[3] = 4;
	coords[2] = -coords[3];
	while (coords[2] <= coords[3])
	{
		draw_circle_row(game, mini_map, coords);
		coords[2]++;
	}
}

void	draw_minimap_player(t_game *game)
{
	t_minimap	*mini_map;
	int			centers[2];

	mini_map = &game->minimap;
	centers[0] = mini_map->x + mini_map->size / 2;
	centers[1] = mini_map->y + mini_map->size / 2;
	draw_player_circle(game, centers[0], centers[1]);
	draw_minimap_cone(game);
}
