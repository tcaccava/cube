/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:25:20 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/20 21:48:44 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	double	ray_offset;
	double	radiant_angle;

	if (argc != 2 || check_file_cub(argv[1]) == 0)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		printf("Error: game init failed (a revoir l'anglais)\n");
		return (1);
	}
	i = 0;
	while (i < DISPLAY_WIDTH)
	{
		ray_offset = game.player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
		radiant_angle = game.player.angle + ray_offset;
		while (radiant_angle < 0)
			radiant_angle += 2 * M_PI;
		while (radiant_angle >= 2 * M_PI)
			radiant_angle -= 2 * M_PI;
		game.rays[i].radiant_angle = radiant_angle;
		game.rays[i].player_angle = game.player.angle;
		game.rays[i].distance = ray_casting(&game, radiant_angle, i);
		i++;
	}
	loop_game(&game);
	return (0);
}
