/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:12 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:33:13 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	count_enemies_in_map(t_game *game)
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
			if (game->map.matrix[y][x] == 'M')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	load_shared_enemy_sprites(t_game *game, t_img shared_sprites[2])
{
	int	width;
	int	height;

	shared_sprites[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_walk.xpm", &width, &height);
	if (!shared_sprites[0].ptr)
		return (0);
	shared_sprites[0].width = width;
	shared_sprites[0].height = height;
	shared_sprites[0].addr = mlx_get_data_addr(shared_sprites[0].ptr,
			&shared_sprites[0].bits_per_pixel, &shared_sprites[0].line_length,
			&shared_sprites[0].endian);
	shared_sprites[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_walk01.xpm", &width, &height);
	if (!shared_sprites[1].ptr)
		return (0);
	shared_sprites[1].width = width;
	shared_sprites[1].height = height;
	shared_sprites[1].addr = mlx_get_data_addr(shared_sprites[1].ptr,
			&shared_sprites[1].bits_per_pixel, &shared_sprites[1].line_length,
			&shared_sprites[1].endian);
	return (1);
}
