/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:35 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:33:36 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_weapon_pickup_sprites(t_game *game)
{
	game->num_weapon_pickup = count_weapons_in_map(game);
	if (game->num_weapon_pickup == 0)
	{
		game->weapon_pickup = NULL;
		return (1);
	}
	game->weapon_pickup = malloc(sizeof(t_weapon_pickup)
			* game->num_weapon_pickup);
	if (!game->weapon_pickup)
		return (0);
	init_weapon_pickup_array(game);
	return (1);
}

int	count_weapons_in_map(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.matrix[y][x] == 'R' || game->map.matrix[y][x] == 'G'
				|| game->map.matrix[y][x] == 'H')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	load_weapon_pickup_sprite(t_game *game, t_weapon_pickup *pickup, char *path)
{
	int	width;
	int	height;

	pickup->sprite.ptr = mlx_xpm_file_to_image(game->mlx, path, &width,
			&height);
	if (!pickup->sprite.ptr)
		return (0);
	pickup->sprite.width = width;
	pickup->sprite.height = height;
	pickup->sprite.addr = mlx_get_data_addr(pickup->sprite.ptr,
			&pickup->sprite.bits_per_pixel, &pickup->sprite.line_length,
			&pickup->sprite.endian);
	return (1);
}

int	set_weapon_positions(t_game *game)
{
	int	y;
	int	x;
	int	weapon_index;

	if (game->num_weapon_pickup == 0)
		return (1);
	weapon_index = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_weapon_cell(game->map.matrix[y][x])
				&& weapon_index < game->num_weapon_pickup)
				setup_weapon_at_position(game, x, y, &weapon_index);
			x++;
		}
		y++;
	}
	return (1);
}

int	load_all_weapons(t_game *game)
{
	if (!load_hands(game))
		return (0);
	if (!load_raygun(game))
		return (0);
	if (!load_portalgun(game))
		return (0);
	if (!load_healgun(game))
		return (0);
	return (1);
}
