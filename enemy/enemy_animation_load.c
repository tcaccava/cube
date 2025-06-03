/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animation_load.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:13 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:14 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	load_enemy_sprite(t_game *game, t_img *sprite, char *path)
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

int	load_enemy_animations(t_game *game, t_enemy *enemy)
{
	if (!load_enemy_sprite(game, &enemy->walk_morty[0],
			"./texture/morty_walk.xpm"))
		return (0);
	if (!load_enemy_sprite(game, &enemy->walk_morty[1],
			"./texture/morty_walk01.xpm"))
		return (0);
	if (!load_enemy_sprite(game, &enemy->shoot_morty[0],
			"./texture/morty_shot.xpm"))
		return (0);
	if (!load_enemy_sprite(game, &enemy->shoot_morty[1],
			"./texture/morty_shot01.xpm"))
		return (0);
	return (1);
}
