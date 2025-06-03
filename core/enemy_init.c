/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:14 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:33:15 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_shared_shoot_sprites(t_game *game, t_img shared_sprites[2])
{
	int	width;
	int	height;

	shared_sprites[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_shot.xpm", &width, &height);
	if (!shared_sprites[0].ptr)
		return (0);
	shared_sprites[0].width = width;
	shared_sprites[0].height = height;
	shared_sprites[0].addr = mlx_get_data_addr(shared_sprites[0].ptr,
			&shared_sprites[0].bits_per_pixel, &shared_sprites[0].line_length,
			&shared_sprites[0].endian);
	shared_sprites[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/morty_shot01.xpm", &width, &height);
	if (!shared_sprites[1].ptr)
		return (0);
	shared_sprites[1].width = width;
	shared_sprites[1].height = height;
	shared_sprites[1].addr = mlx_get_data_addr(shared_sprites[1].ptr,
			&shared_sprites[1].bits_per_pixel, &shared_sprites[1].line_length,
			&shared_sprites[1].endian);
	return (1);
}

static int	load_single_sprite(t_game *game, t_img *img, char *path)
{
	int	width;
	int	height;

	img->ptr = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->ptr)
		return (0);
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (1);
}

int	load_shared_death_sprites(t_game *game, t_img shared_sprites[3])
{
	if (!load_single_sprite(game, &shared_sprites[0],
			"./texture/morty_death.xpm"))
		return (0);
	if (!load_single_sprite(game, &shared_sprites[1],
			"./texture/morty_death01.xpm"))
	{
		shared_sprites[1] = shared_sprites[0];
		return (1);
	}
	if (!load_single_sprite(game, &shared_sprites[2],
			"./texture/morty_death02.xpm"))
	{
		shared_sprites[2] = shared_sprites[0];
		return (1);
	}
	return (1);
}

static void	init_enemy(t_enemy *e, t_enemy_sprites *sprites, t_img *tex)
{
	*e = (t_enemy){.x = 0.0, .y = 0.0, .angle = 0.0, .health = 25,
		.state = IDLE, .speed = 0.05, .cooldown = 0, .distance_to_player = 0.0,
		.texture = tex, .active = 1, .sees_player = 0, .death_timer = 0};
	e->walk_morty[0] = sprites->walk[0];
	e->walk_morty[1] = sprites->walk[1];
	e->shoot_morty[0] = sprites->shoot[0];
	e->shoot_morty[1] = sprites->shoot[1];
	e->death_morty[0] = sprites->death[0];
	e->death_morty[1] = sprites->death[1];
	e->death_morty[2] = sprites->death[2];
	e->animation.current_frame = 0;
	e->animation.frame_counter = 0;
}

int	init_all_enemies(t_game *game)
{
	t_enemy_sprites	sprites;
	int				i;

	if (!load_shared_enemy_sprites(game, sprites.walk)
		|| !load_shared_shoot_sprites(game, sprites.shoot)
		|| !load_shared_death_sprites(game, sprites.death))
		return (printf("Error: failed to load enemy textures\n"), 0);
	game->num_enemies = count_enemies_in_map(game);
	game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
	if (!game->enemies)
		return (0);
	i = 0;
	while (i < game->num_enemies)
		init_enemy(&game->enemies[i++], &sprites, &game->map.enemy_texture);
	if (!set_enemy_pos(game))
		printf("No enemy found in map");
	return (1);
}
