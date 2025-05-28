/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:34:11 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/28 19:54:55 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static t_point	minimap_cone_coords(t_game *game, double angle, int dist)
{
	t_point		result;
	t_minimap	*mini;

	mini = &game->minimap;
	result.x = mini->x + mini->size / 2 + cos(angle) * dist;
	result.y = mini->y + mini->size / 2 + sin(angle) * dist;
	return (result);
}

static void	draw_cone_pixel(t_game *game, double angle, int distance)
{
	t_point		p;
	t_minimap	*mini_map;
	char		*pixel;

	mini_map = &game->minimap;
	p = minimap_cone_coords(game, angle, distance);
	if (p.x >= mini_map->x + mini_map->border && p.x < mini_map->x
		+ mini_map->size - mini_map->border && p.y >= mini_map->y
		+ mini_map->border && p.y < mini_map->y + mini_map->size
		- mini_map->border)
	{
		pixel = game->screen.addr + (p.y * game->screen.line_length + p.x
				* (game->screen.bits_per_pixel / 8));
		*(unsigned int *)pixel = mini_map->player_color;
	}
}

static void	draw_cone_line(t_game *game, double angle)
{
	int	i;

	i = 0;
	while (i < 45)
	{
		draw_cone_pixel(game, angle, i);
		i++;
	}
}

void	draw_minimap_cone(t_game *game)
{
	double	fov;
	double	start_angle;
	double	end_angle;
	double	step;
	double	angle;

	fov = M_PI / 2;
	start_angle = game->player.angle - fov / 2;
	end_angle = game->player.angle + fov / 2;
	step = 0.01;
	angle = start_angle;
	while (angle <= end_angle)
	{
		draw_cone_line(game, angle);
		angle += step;
	}
}
