/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:07:47 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 23:40:41 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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

void	store_ray_info(t_game *game, int column_x, t_ray_data *data)
{
	game->rays[column_x].distance = data->distance;
	game->rays[column_x].wall_hit_x = data->hit_x;
	game->rays[column_x].wall_hit_y = data->hit_y;
	game->rays[column_x].hit_vertical = data->is_vertical;
	game->rays[column_x].hit_type = data->hit_type;
}
