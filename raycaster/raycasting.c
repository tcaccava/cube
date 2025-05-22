/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:09:42 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/21 23:10:43 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_intersect	v_intersection(int x_player, int y_player, double radiant_angle)
{
	t_intersect	v;

	double first_x, first_y;
	v.x = x_player;
	v.y = y_player;
	v.step_x = 0;
	v.step_y = 0;
	if (fabs(cos(radiant_angle)) < 0.000001)
		return (v);
	if (cos(radiant_angle) > 0)
	{
		first_x = floor(x_player / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		v.step_x = TILE_SIZE;
	}
	else
	{
		first_x = floor(x_player / TILE_SIZE) * TILE_SIZE;
		v.step_x = -TILE_SIZE;
		first_x -= 0.001;
	}
	first_y = y_player + (first_x - x_player) * tan(radiant_angle);
	v.step_y = tan(radiant_angle) * v.step_x;
	v.x = first_x;
	v.y = first_y;
	return (v);
}

t_intersect	h_intersection(int x_player, int y_player, double radiant_angle)
{
	t_intersect	h;

	double first_x, first_y;
	h.x = x_player;
	h.y = y_player;
	h.step_x = 0;
	h.step_y = 0;
	if (fabs(sin(radiant_angle)) < 0.000001)
		return (h);
	if (sin(radiant_angle) > 0)
	{
		first_y = floor(y_player / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		h.step_y = TILE_SIZE;
	}
	else
	{
		first_y = floor(y_player / TILE_SIZE) * TILE_SIZE;
		h.step_y = -TILE_SIZE;
		first_y -= 0.001;
	}
	if (fabs(tan(radiant_angle)) > 0.000001)
		first_x = x_player + (first_y - y_player) / tan(radiant_angle);
	else
		first_x = x_player;
	h.step_x = h.step_y / tan(radiant_angle);
	h.x = first_x;
	h.y = first_y;
	return (h);
}


int	is_not_wall(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (0);
	if (map->matrix[map_y][map_x] == '1' || map->matrix[map_y][map_x] == 'D'
		|| map->matrix[map_y][map_x] == 'P' || map->matrix[map_y][map_x] == 'i'
		|| map->matrix[map_y][map_x] == 'd' || map->matrix[map_y][map_x] == 'M')
		return (0);
	else
		return (1);
}

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

void	store_ray_info(t_game *game, int column_x, double distance,
		double hit_x, double hit_y, int is_vertical, char hit_type)
{
	game->rays[column_x].distance = distance;
	game->rays[column_x].wall_hit_x = hit_x;
	game->rays[column_x].wall_hit_y = hit_y;
	game->rays[column_x].hit_vertical = is_vertical;
	game->rays[column_x].hit_type = hit_type;
}

double	ray_casting(t_game *game, double radiant_angle, int column_x)
{
	t_intersect	v;
	t_intersect	h;
	double		epsilon;
	int			max_iterations;
	int			iter;
	double		dist_v;
	double		dist_h;
	char		hit_type_v;
	char		hit_type_h;

	radiant_angle = normalize_angle(radiant_angle);
	while (radiant_angle < 0)
		radiant_angle += 2 * M_PI;
	while (radiant_angle >= 2 * M_PI)
		radiant_angle -= 2 * M_PI;
	v = v_intersection(game->player.x, game->player.y, radiant_angle);
	h = h_intersection(game->player.x, game->player.y, radiant_angle);
	epsilon = 0.00001;
	max_iterations = 1000;
	iter = 0;
	while (is_not_wall(&game->map, v.x, v.y) && iter < max_iterations)
	{
		v.x += v.step_x;
		v.y += v.step_y;
		iter++;
	}
	iter = 0;
	while (is_not_wall(&game->map, h.x, h.y) && iter < max_iterations)
	{
		h.x += h.step_x;
		h.y += h.step_y;
		iter++;
	}
	dist_v = sqrt(pow(v.x - game->player.x, 2) + pow(v.y - game->player.y, 2));
	dist_h = sqrt(pow(h.x - game->player.x, 2) + pow(h.y - game->player.y, 2));
	hit_type_v = get_hit_type(&game->map, v.x, v.y);
	hit_type_h = get_hit_type(&game->map, h.x, h.y);
	if (fabs(dist_v - dist_h) < epsilon)
	{
		store_ray_info(game, column_x, dist_h, h.x, h.y, 0, hit_type_h);
		return (dist_h);
	}
	if (dist_v < dist_h)
	{
		store_ray_info(game, column_x, dist_v, v.x, v.y, 1, hit_type_v);
		return (dist_v);
	}
	else
	{
		store_ray_info(game, column_x, dist_h, h.x, h.y, 0, hit_type_h);
		return (dist_h);
	}
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
