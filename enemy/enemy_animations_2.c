/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animations_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:31:53 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:09:13 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	load_enemy_animations_part1(t_game *game, t_enemy *enemy)
{
	enemy->walk_morty[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_walk_0.xpm", &enemy->walk_morty[0].width,
			&enemy->walk_morty[0].height);
	enemy->walk_morty[0].addr = mlx_get_data_addr(enemy->walk_morty[0].ptr,
			&enemy->walk_morty[0].bits_per_pixel,
			&enemy->walk_morty[0].line_length, &enemy->walk_morty[0].endian);
	enemy->walk_morty[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_walk_1.xpm", &enemy->walk_morty[1].width,
			&enemy->walk_morty[1].height);
	enemy->walk_morty[1].addr = mlx_get_data_addr(enemy->walk_morty[1].ptr,
			&enemy->walk_morty[1].bits_per_pixel,
			&enemy->walk_morty[1].line_length, &enemy->walk_morty[1].endian);
	enemy->shoot_morty[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_shoot_0.xpm", &enemy->shoot_morty[0].width,
			&enemy->shoot_morty[0].height);
	enemy->shoot_morty[0].addr = mlx_get_data_addr(enemy->shoot_morty[0].ptr,
			&enemy->shoot_morty[0].bits_per_pixel,
			&enemy->shoot_morty[0].line_length, &enemy->shoot_morty[0].endian);
	enemy->shoot_morty[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_shoot_1.xpm", &enemy->shoot_morty[1].width,
			&enemy->shoot_morty[1].height);
	enemy->shoot_morty[1].addr = mlx_get_data_addr(enemy->shoot_morty[1].ptr,
			&enemy->shoot_morty[1].bits_per_pixel,
			&enemy->shoot_morty[1].line_length, &enemy->shoot_morty[1].endian);
}

void	load_enemy_animations_part2(t_game *game, t_enemy *enemy)
{
	enemy->death_morty[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_dead_0.xpm", &enemy->death_morty[0].width,
			&enemy->death_morty[0].height);
	enemy->death_morty[0].addr = mlx_get_data_addr(enemy->death_morty[0].ptr,
			&enemy->death_morty[0].bits_per_pixel,
			&enemy->death_morty[0].line_length, &enemy->death_morty[0].endian);
	enemy->death_morty[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_dead_1.xpm", &enemy->death_morty[1].width,
			&enemy->death_morty[1].height);
	enemy->death_morty[1].addr = mlx_get_data_addr(enemy->death_morty[1].ptr,
			&enemy->death_morty[1].bits_per_pixel,
			&enemy->death_morty[1].line_length, &enemy->death_morty[1].endian);
	enemy->death_morty[2].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/morty_dead_2.xpm", &enemy->death_morty[2].width,
			&enemy->death_morty[2].height);
	enemy->death_morty[2].addr = mlx_get_data_addr(enemy->death_morty[2].ptr,
			&enemy->death_morty[2].bits_per_pixel,
			&enemy->death_morty[2].line_length, &enemy->death_morty[2].endian);
}

int	load_death_animations_part1(t_game *game, t_enemy *enemy)
{
	int	width;
	int	height;

	enemy->death_morty[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_death.xpm", &width, &height);
	if (!enemy->death_morty[0].ptr)
		return (0);
	enemy->death_morty[0].width = width;
	enemy->death_morty[0].height = height;
	enemy->death_morty[0].addr = mlx_get_data_addr(enemy->death_morty[0].ptr,
			&enemy->death_morty[0].bits_per_pixel,
			&enemy->death_morty[0].line_length, &enemy->death_morty[0].endian);
	enemy->death_morty[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_death01.xpm", &width, &height);
	if (!enemy->death_morty[1].ptr)
		return (1);
	enemy->death_morty[1].width = width;
	enemy->death_morty[1].height = height;
	enemy->death_morty[1].addr = mlx_get_data_addr(enemy->death_morty[1].ptr,
			&enemy->death_morty[1].bits_per_pixel,
			&enemy->death_morty[1].line_length, &enemy->death_morty[1].endian);
	return (1);
}

int	load_death_animations_part2(t_game *game, t_enemy *enemy)
{
	int	height;
	int	width;

	enemy->death_morty[2].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_death02.xpm", &width, &height);
	if (!enemy->death_morty[2].ptr)
		return (2);
	enemy->death_morty[2].width = width;
	enemy->death_morty[2].height = height;
	enemy->death_morty[2].addr = mlx_get_data_addr(enemy->death_morty[2].ptr,
			&enemy->death_morty[2].bits_per_pixel,
			&enemy->death_morty[2].line_length, &enemy->death_morty[2].endian);
	return (1);
}
