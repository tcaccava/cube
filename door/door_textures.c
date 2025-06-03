/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:54 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:55 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	load_door_textures(t_game *game)
{
	if (!load_closed_door_texture(game))
		return (0);
	if (!load_open_door_texture(game))
		return (0);
	if (!load_shot_door_textures(game))
		return (0);
	return (1);
}

int	load_closed_door_texture(t_game *game)
{
	int	width;
	int	height;

	game->map.door_texture.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/door.xpm", &width, &height);
	if (!game->map.door_texture.ptr)
		return (0);
	setup_texture_data(&game->map.door_texture, width, height);
	return (1);
}

int	load_open_door_texture(t_game *game)
{
	int	width;
	int	height;

	game->map.open_door_texture.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/door_open.xpm", &width, &height);
	if (!game->map.open_door_texture.ptr)
		return (0);
	setup_texture_data(&game->map.open_door_texture, width, height);
	return (1);
}

int	load_shot_door_textures(t_game *game)
{
	if (!load_door_shooted_texture(game))
		return (0);
	if (!load_open_door_shooted_texture(game))
		return (0);
	return (1);
}

void	setup_texture_data(t_img *texture, int width, int height)
{
	texture->width = width;
	texture->height = height;
	texture->addr = mlx_get_data_addr(texture->ptr,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
}
