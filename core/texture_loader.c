/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:30 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:35:44 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_basic_textures(t_game *game)
{
	int	width;
	int	height;

	game->map.wall_texture.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/wall.xpm", &width, &height);
	if (!game->map.wall_texture.ptr)
		return (0);
	game->map.wall_texture.width = width;
	game->map.wall_texture.height = height;
	game->map.wall_texture.addr = mlx_get_data_addr (game->map.wall_texture.ptr,
			&game->map.wall_texture.bits_per_pixel,
			&game->map.wall_texture.line_length,
			&game->map.wall_texture.endian);
	game->map.floor_texture.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/floor.xpm", &width, &height);
	if (!game->map.floor_texture.ptr)
		return (0);
	game->map.floor_texture.width = width;
	game->map.floor_texture.height = height;
	game->map.floor_texture.addr = mlx_get_data_addr (
			game->map.floor_texture.ptr,
			&game->map.floor_texture.bits_per_pixel,
			&game->map.floor_texture.line_length,
			&game->map.floor_texture.endian);
	return (1);
}

int	load_special_textures(t_game *game)
{
	int	width;
	int	height;

	game->map.wall_portal_texture.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/wall_portal.xpm", &width, &height);
	if (!game->map.wall_portal_texture.ptr)
		return (0);
	game->map.wall_portal_texture.width = width;
	game->map.wall_portal_texture.height = height;
	game->map.wall_portal_texture.addr = mlx_get_data_addr (
			game->map.wall_portal_texture.ptr,
			&game->map.wall_portal_texture.bits_per_pixel,
			&game->map.wall_portal_texture.line_length,
			&game->map.wall_portal_texture.endian);
	game->map.wall_shooted_texture.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/wall_shooted.xpm", &width, &height);
	game->map.wall_shooted_texture.width = width;
	game->map.wall_shooted_texture.height = height;
	game->map.wall_shooted_texture.addr = mlx_get_data_addr (
			game->map.wall_shooted_texture.ptr,
			&game->map.wall_shooted_texture.bits_per_pixel,
			&game->map.wall_shooted_texture.line_length,
			&game->map.wall_shooted_texture.endian);
	return (1);
}

static int	load_texture(t_game *game, t_img *tex, char *path)
{
	int	width;
	int	height;

	if (!game->mlx)
	{
		return (0);
	}
	tex->ptr = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!tex->ptr)
	{
		return (0);
	}
	tex->width = width;
	tex->height = height;
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (1);
}

int	load_directional_textures(t_game *game, t_texture_paths *paths)
{
	if (!load_texture(game, &game->map.north, paths->north))
		return (0);
	if (!load_texture(game, &game->map.south, paths->south))
		return (0);
	if (!load_texture(game, &game->map.east, paths->east))
		return (0);
	if (!load_texture(game, &game->map.west, paths->west))
		return (0);
	return (1);
}
