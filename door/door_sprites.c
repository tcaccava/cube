/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:48 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:49 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	load_open_door_sprites(t_game *game)
{
	init_open_door_array(game);
	if (game->num_open_doors == 0)
		return (1);
	return (load_all_door_sprites(game));
}

void	init_open_door_array(t_game *game)
{
	game->num_open_doors = count_open_doors_in_map(game);
	if (game->num_open_doors == 0)
	{
		game->open_doors = NULL;
		return ;
	}
	game->open_doors = malloc(sizeof(t_open_door) * game->num_open_doors);
}

int	count_open_doors_in_map(t_game *game)
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
			if (game->map.matrix[y][x] == 'O')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	load_all_door_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_open_doors)
	{
		if (!load_single_door_sprite(game, i))
			return (0);
		i++;
	}
	return (1);
}

int	set_open_door_positions(t_game *game)
{
	int	y;
	int	x;
	int	door_index;

	if (game->num_open_doors == 0)
		return (1);
	door_index = 0;
	y = 0;
	while (y < game->map.height && door_index < game->num_open_doors)
	{
		x = 0;
		while (x < game->map.width && door_index < game->num_open_doors)
		{
			if (game->map.matrix[y][x] == 'O')
				setup_door_at_position(game, x, y, &door_index);
			x++;
		}
		y++;
	}
	return (1);
}
