/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:25:20 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:25:28 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_player(t_player *player)
{
	player->x = DISPLAY_WIDTH / 2;
	player->y = DISPLAY_HEIGHT / 2;
	player->angle = M_PI / 3;
	player->fov = player->angle;
	update_camera_vectors(player);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->turn_back = false;
	player->current_weapon = PORTALGUN;
	player->health = 100;
	player->weapon.current_state = WEAPON_NEUTRE;
	player->weapon.frame = 0;
	player->weapon.frame_delay = 0;
	player->weapon.is_firing = 0;
	player->fire_cooldown = 0;
}

void	init_rays(t_game *game)
{
	int		i;
	double	ray_offset;
	double	radiant_angle;

	i = 0;
	while (i < DISPLAY_WIDTH)
	{
		ray_offset = game->player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
		radiant_angle = game->player.angle + ray_offset;
		while (radiant_angle < 0)
			radiant_angle += 2 * M_PI;
		while (radiant_angle >= 2 * M_PI)
			radiant_angle -= 2 * M_PI;
		game->rays[i].radiant_angle = radiant_angle;
		game->rays[i].player_angle = game->player.angle;
		game->rays[i].distance = ray_casting(game, radiant_angle, i);
		i++;
	}
}

static int	init_standard_mode(t_game *game, char **argv)
{
	if (check_file_cub(argv[1]) == 0)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (0);
	}
	if (!init_game(game, argv[1]))
	{
		printf("Error: game init failed\n");
		return (0);
	}
	return (1);
}

static int	init_texture_mode(t_game *game, char **argv)
{
	t_texture_paths	paths;

	if (check_file_cub(argv[1]) == 0)
		return (0);
	paths.north = argv[2];
	paths.south = argv[3];
	paths.east = argv[4];
	paths.west = argv[5];
	if (!init_game_with_4_textures(game, argv[1], &paths))
	{
		printf("Error: game init failed\n");
		return (0);
	}
	return (1);
}

int	init_game_mode(t_game *game, int argc, char **argv)
{
	if (argc == 2)
		return (init_standard_mode(game, argv));
	else if (argc == 6)
		return (init_texture_mode(game, argv));
	else
		return (0);
}
