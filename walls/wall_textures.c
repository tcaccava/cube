/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:36 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:37 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static t_img	*get_vertical_texture(t_game *game, t_ray *ray)
{
	if (cos(ray->radiant_angle) > 0)
		return (&game->map.east);
	else
		return (&game->map.west);
}

static t_img	*get_horizontal_texture(t_game *game, t_ray *ray)
{
	if (sin(ray->radiant_angle) > 0)
		return (&game->map.south);
	else
		return (&game->map.north);
}

static t_img	*get_directional_texture(t_game *game, t_ray *ray)
{
	if (ray->hit_vertical)
		return (get_vertical_texture(game, ray));
	else
		return (get_horizontal_texture(game, ray));
}

t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (game->map.north.ptr != NULL)
		return (get_directional_texture(game, ray));
	else
		return (&game->map.wall_texture);
}
