/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:10:51 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/12 13:16:43 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	validate_player_spawn_count(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->matrix[y][x] && x < (int)ft_strlen(map->matrix[y]))
		{
			if (is_valid_playable_char(map->matrix[y][x]))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count == 0)
		return (printf("Error: No player spawn position found in map\n"), 0);
	if (player_count > 1)
		return (printf("Error: Multiple player positions found (%d total)\n",
				player_count), 0);
	return (1);
}
