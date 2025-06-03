/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_loader_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:32 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:33:33 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	is_weapon_cell(char cell)
{
	if (cell == 'R' || cell == 'G' || cell == 'H')
		return (1);
	return (0);
}

void	setup_weapon_at_position(t_game *game, int x, int y, int *weapon_index)
{
	char	cell;

	game->weapon_pickup[*weapon_index].x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->weapon_pickup[*weapon_index].y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	cell = game->map.matrix[y][x];
	if (cell == 'R')
	{
		game->weapon_pickup[*weapon_index].weapon_type = RAYGUN;
		load_weapon_pickup_sprite(game, &game->weapon_pickup[*weapon_index],
			"./texture/raygun_pickup.xpm");
	}
	else if (cell == 'G')
	{
		game->weapon_pickup[*weapon_index].weapon_type = PORTALGUN;
		load_weapon_pickup_sprite(game, &game->weapon_pickup[*weapon_index],
			"./texture/portalgun_pickup.xpm");
	}
	else if (cell == 'H')
	{
		game->weapon_pickup[*weapon_index].weapon_type = HEALGUN;
		load_weapon_pickup_sprite(game, &game->weapon_pickup[*weapon_index],
			"./texture/healgun_pickup.xpm");
	}
	game->weapon_pickup[*weapon_index].active = 1;
	(*weapon_index)++;
}

void	disable_weapon_pickup_at_position(t_game *game, int map_x, int map_y,
		int weapon_type)
{
	int	i;
	int	weapon_map_x;
	int	weapon_map_y;

	i = 0;
	while (i < game->num_weapon_pickup)
	{
		if (game->weapon_pickup[i].active)
		{
			weapon_map_x = (int)(game->weapon_pickup[i].x / TILE_SIZE);
			weapon_map_y = (int)(game->weapon_pickup[i].y / TILE_SIZE);
			if (weapon_map_x == map_x && weapon_map_y == map_y
				&& game->weapon_pickup[i].weapon_type == weapon_type)
			{
				game->weapon_pickup[i].active = 0;
				return ;
			}
		}
		i++;
	}
}

int	load_hands(t_game *game)
{
	int	width;
	int	height;

	game->weapons[HANDS][0].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/hand.xpm", &width, &height);
	if (!game->weapons[HANDS][0].ptr)
		return (0);
	game->weapons[HANDS][0].width = width;
	game->weapons[HANDS][0].height = height;
	game->weapons[HANDS][0].addr = mlx_get_data_addr(game->weapons[HANDS][0]
			.ptr, &game->weapons[HANDS][0].bits_per_pixel,
			&game->weapons[HANDS][0].line_length,
			&game->weapons[HANDS][0].endian);
	game->weapons[HANDS][1] = game->weapons[HANDS][0];
	game->weapons[HANDS][2] = game->weapons[HANDS][0];
	return (1);
}
