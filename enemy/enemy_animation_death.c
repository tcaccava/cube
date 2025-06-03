/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animation_death.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:11 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:12 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	load_death_sprite(t_game *game, t_img *sprite, char *path)
{
	int	width;
	int	height;

	sprite->ptr = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!sprite->ptr)
		return (0);
	sprite->width = width;
	sprite->height = height;
	sprite->addr = mlx_get_data_addr(sprite->ptr, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian);
	return (1);
}

int	load_death_animations(t_game *game, t_enemy *enemy)
{
	if (!load_death_sprite(game, &enemy->death_morty[0],
			"./texture/morty_death.xpm"))
		return (0);
	if (!load_death_sprite(game, &enemy->death_morty[1],
			"./texture/morty_death01.xpm"))
		return (1);
	if (!load_death_sprite(game, &enemy->death_morty[2],
			"./texture/morty_death02.xpm"))
		return (1);
	return (1);
}
