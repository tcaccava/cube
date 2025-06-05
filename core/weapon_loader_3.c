/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_loader_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:34 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 16:55:16 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_single_weapon_texture(void *mlx, t_img *tex, char *path)
{
	int	width;
	int	height;

	tex->ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!tex->ptr)
	{
		printf("Error loading texture: %s\n", path);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	tex->width = width;
	tex->height = height;
	return (1);
}

int	load_weapon_textures(void *mlx, t_img weapon_textures[3], int weapon_type)
{
	const char	*paths[MAX_WEAPONS][3] = {
	{"./texture/hands.xpm", "./texture/hands.xpm", "./texture/hands.xpm"},
	{"./texture/w_portalgun.xpm", "./texture/w_portalgun.xpm",
		"./texture/w_portalgun.xpm"},
	{"./texture/w_raygun.xpm", "./texture/w_raygun_prefire.xpm",
		"./texture/w_raygun_fire.xpm"},
	{"./texture/w_healgun.xpm", "./texture/w_healgun.xpm",
		"./texture/w_healgun.xpm"}
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (!load_single_weapon_texture(mlx, &weapon_textures[i],
				(char *)paths[weapon_type][i]))
			return (0);
		i++;
	}
	return (1);
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
