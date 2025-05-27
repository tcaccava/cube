/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:08:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 23:38:20 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

double	no_fish_eye(double min_distance, double radiant_angle,
		double player_angle)
{
	double	angle_diff;

	angle_diff = radiant_angle - player_angle;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	return (min_distance * cos(angle_diff));
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

double	ray_casting(t_game *game, double radiant_angle, int column_x)
{
	t_ray_calc	calc;
	t_intersect	v;
	t_intersect	h;

	radiant_angle = normalize_angle(radiant_angle);
	v = v_intersection(game->player.x, game->player.y, radiant_angle);
	h = h_intersection(game->player.x, game->player.y, radiant_angle);
	cast_intersections(game, &v, &h);
	calc = (t_ray_calc){&v, &h, column_x};
	select_ray_hit(game, &calc);
	return (game->rays[column_x].distance);
}
