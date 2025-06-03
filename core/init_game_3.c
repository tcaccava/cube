/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:22 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:33:23 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player_basics(t_player *player)
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
	player->health = 100;
	player->move_speed = 10;
	player->rot_speed = 0.05;
}

void	init_player_weapons(t_player *player)
{
	player->current_weapon = HANDS;
	player->weapon.current_state = WEAPON_NEUTRE;
	player->weapon.frame = 0;
	player->weapon.frame_delay = 0;
	player->weapon.is_firing = 0;
	player->fire_cooldown = 0;
	player->has_weapon[HANDS] = true;
	player->has_weapon[RAYGUN] = false;
	player->has_weapon[PORTALGUN] = false;
	player->has_weapon[HEALGUN] = false;
	player->healgun_ammo = 0;
	player->healgun_is_loaded = 0;
	player->healgun_animating = 0;
	player->healgun_anim_frame = 0;
	player->healgun_anim_timer = 0;
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

int	init_game_with_4_textures(t_game *game, char *map_file,
		t_texture_paths *paths)
{
	init_player(&game->player);
	game->player.game = game;
	if (!init_mlx_window(game))
		return (0);
	if (!init_map_and_player(game, map_file))
		return (0);
	game->current_weapon = HANDS;
	if (!load_special_textures(game))
		return (0);
	if (!load_all_weapons(game))
		return (0);
	if (!load_door_textures(game))
		return (0);
	if (!load_directional_textures(game, paths))
		return (0);
	if (!init_all_enemies(game))
		return (0);
	init_portals(game);
	init_ui_components(game);
	return (1);
}
