/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:50 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:51 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_door(t_game *game, int column_x, t_render *renderer, t_ray *ray)
{
	calculate_door_texture_coordinates(renderer, ray);
	render_door_column(game, column_x, renderer);
}

void	render_open_door(t_game *game, int column_x, t_render *renderer,
		t_ray *ray)
{
	double	pos_in_cell;

	calculate_door_texture_coordinates(renderer, ray);
	pos_in_cell = get_position_in_cell(ray);
	if (is_door_frame_position(pos_in_cell))
		render_door_column(game, column_x, renderer);
}

void	calculate_door_texture_coordinates(t_render *renderer, t_ray *ray)
{
	if (ray->hit_vertical)
		renderer->tex_x = (int)(ray->wall_hit_y) % TILE_SIZE;
	else
		renderer->tex_x = (int)(ray->wall_hit_x) % TILE_SIZE;
}

double	get_position_in_cell(t_ray *ray)
{
	double	pos_in_cell;

	if (ray->hit_vertical)
		pos_in_cell = fmod(ray->wall_hit_y, TILE_SIZE);
	else
		pos_in_cell = fmod(ray->wall_hit_x, TILE_SIZE);
	if (pos_in_cell < 0)
		pos_in_cell += TILE_SIZE;
	return (pos_in_cell);
}

int	is_door_frame_position(double pos_in_cell)
{
	double	edge_size;

	edge_size = TILE_SIZE * 0.2;
	if (pos_in_cell <= edge_size)
		return (1);
	if (pos_in_cell >= TILE_SIZE - edge_size)
		return (1);
	return (0);
}
