/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_specific.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:27 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:28 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	load_hands(t_game *game)
{
	int	width;
	int	height;

	game->weapons[HANDS][0].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/hand.xpm", &width, &height);
	if (!game->weapons[HANDS][0].ptr)
	{
		printf("Error loading hands texture\n");
		return (0);
	}
	setup_hands_texture(game, width, height);
	return (1);
}

void	setup_hands_texture(t_game *game, int width, int height)
{
	game->weapons[HANDS][0].width = width;
	game->weapons[HANDS][0].height = height;
	game->weapons[HANDS][0].addr = mlx_get_data_addr(game->weapons[HANDS][0]
			.ptr, &game->weapons[HANDS][0].bits_per_pixel,
			&game->weapons[HANDS][0].line_length,
			&game->weapons[HANDS][0].endian);
	game->weapons[HANDS][1] = game->weapons[HANDS][0];
	game->weapons[HANDS][2] = game->weapons[HANDS][0];
}

int	load_raygun(t_game *game)
{
	if (!load_weapon_textures(game->mlx, game->weapons[RAYGUN], RAYGUN))
	{
		printf("Error loading Ray Gun textures\n");
		return (0);
	}
	return (1);
}

int	load_portalgun(t_game *game)
{
	if (!load_weapon_textures(game->mlx, game->weapons[PORTALGUN], PORTALGUN))
	{
		printf("Error loading Portal Gun textures\n");
		return (0);
	}
	return (1);
}

int	load_healgun(t_game *game)
{
	if (!load_weapon_textures(game->mlx, game->weapons[HEALGUN], HEALGUN))
	{
		printf("Error loading Heal Gun textures\n");
		return (0);
	}
	return (1);
}
