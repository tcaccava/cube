/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_pickup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:38 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:39 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
			if (is_weapon_cell(game->map.matrix[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	is_weapon_cell(char cell)
{
	if (cell == 'R')
		return (1);
	if (cell == 'G')
		return (1);
	if (cell == 'H')
		return (1);
	return (0);
}

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

void	init_weapon_pickup_array(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_weapon_pickup)
	{
		game->weapon_pickup[i].active = 0;
		game->weapon_pickup[i].sprite.ptr = NULL;
		i++;
	}
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
