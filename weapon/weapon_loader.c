/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:11 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:12 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
	const char	*paths[MAX_WEAPONS][3];
	int			i;

	init_weapon_paths(paths);
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

void	init_weapon_paths(const char paths[MAX_WEAPONS][3])
{
	init_hands_paths(paths[HANDS]);
	init_portalgun_paths(paths[PORTALGUN]);
	init_raygun_paths(paths[RAYGUN]);
	init_healgun_paths(paths[HEALGUN]);
}
