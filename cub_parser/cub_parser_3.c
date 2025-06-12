/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:38:40 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/12 10:51:50 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	setup_map_data(t_scene_data *scene, t_game *game)
{
	if (scene->map_count == 0)
		return (printf("Error: No map found\n"), 0);
	game->map.matrix[scene->map_count] = NULL;
	game->map.height = scene->map_count;
	game->map.width = calculate_map_width(game);
	game->map.floor_color = scene->floor_color;
	game->map.sky_color = scene->ceiling_color;
	return (1);
}

static int	setup_player(t_game *game)
{
	if (!init_mlx_window(game))
		return (printf("Error: MLX init failed\n"), 0);
	init_player(&game->player);
	game->player.game = game;
	if (!set_player_pos(game))
		return (printf("Error: No player position found\n"), 0);
	return (1);
}

static int	load_textures(t_game *game, t_scene_data *scene)
{
	t_texture_paths	paths;

	paths.north = scene->north_texture;
	paths.south = scene->south_texture;
	paths.east = scene->east_texture;
	paths.west = scene->west_texture;
	if (!load_directional_textures(game, &paths))
		return (printf("Error: Failed to load directional textures\n"), 0);
	if (!load_special_textures(game))
		return (printf("Error: Failed to load special textures\n"), 0);
	if (!load_door_textures(game))
		return (printf("Error: Failed to load door textures\n"), 0);
	return (1);
}

static int	setup_weapons_and_sprites(t_game *game)
{
	game->current_weapon = HANDS;
	if (!load_all_weapons(game))
		return (printf("Error: Failed to load weapons\n"), 0);
	if (!load_weapon_pickup_sprites(game))
		return (printf("Error: Failed to load weapon pickups\n"), 0);
	if (!set_weapon_positions(game))
		return (printf("Error: Failed to set weapon positions\n"), 0);
	if (!load_open_door_sprites(game))
		return (printf("Error: Failed to load door sprites\n"), 0);
	if (!set_open_door_positions(game))
		return (printf("Error: Failed to set door positions\n"), 0);
	return (1);
}

int	finalize_parsing(t_scene_data *scene, t_game *game)
{
	if (!validate_textures(scene))
		return (cleanup_scene(scene), 0);
	if (!setup_map_data(scene, game))
		return (cleanup_scene(scene), 0);
	if (!validate_map(&game->map))
		return (cleanup_scene(scene), 0);
	if (!setup_player(game))
		return (cleanup_scene(scene), cleanup_map_matrix(game),
			cleanup_mlx(game), 0);
	if (!load_textures(game, scene))
		return (cleanup_scene(scene), cleanup_map_matrix(game),
			cleanup_map_textures(game), cleanup_mlx(game), 0);
	if (!setup_weapons_and_sprites(game))
		return (cleanup_scene(scene), cleanup_map_matrix(game),
			cleanup_map_textures(game), cleanup_weapons(game),
			cleanup_entities(game), cleanup_mlx(game), 0);
	if (!init_all_enemies(game))
		return (cleanup_scene(scene), cleanup_map_matrix(game),
			cleanup_map_textures(game), cleanup_weapons(game),
			cleanup_entities(game), cleanup_mlx(game), 0);
	init_portals(game);
	init_ui_components(game);
	cleanup_scene(scene);
	printf("✅ Game initialized!\n");
	return (1);
}
