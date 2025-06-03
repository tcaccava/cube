/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:43 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:44 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle = angle + (2 * M_PI);
	while (angle >= 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

char	get_hit_type(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x >= 0 && map_x < map->width && map_y >= 0 && map_y < map->height)
		return (map->matrix[map_y][map_x]);
	else
		return ('1');
}

void	store_ray_info(t_game *game, int column_x, t_ray_hit_data *hit_data)
{
	game->rays[column_x].distance = hit_data->distance;
	game->rays[column_x].wall_hit_x = hit_data->hit_x;
	game->rays[column_x].wall_hit_y = hit_data->hit_y;
	game->rays[column_x].hit_vertical = hit_data->is_vertical;
	game->rays[column_x].hit_type = hit_data->hit_type;
}

double	no_fish_eye(double min_distance, double radiant_angle,
		double player_angle)
{
	double	angle_diff;
	double	corrected_dist;

	angle_diff = radiant_angle - player_angle;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	corrected_dist = min_distance * (cos(angle_diff));
	return (corrected_dist);
}

int	calc_wall_height(double corrected_dist)
{
	double	distance_to_projection_plane;
	double	wall_height;

	distance_to_projection_plane = (DISPLAY_WIDTH / 2.0) / tan(FOV / 2.0);
	corrected_dist = fmax(corrected_dist, 0.1);
	wall_height = (TILE_SIZE / corrected_dist) * distance_to_projection_plane;
	return ((int)fmin(wall_height, DISPLAY_HEIGHT * 3));
}
