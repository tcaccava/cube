/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:32:51 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:25:32 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	init_game_with_4_textures(t_game *game, char *map_file,
		t_texture_paths *paths)
{
	init_player(&game->player);
	game->player.game = game;
	if (!init_mlx_window(game))
		return (0);
	if (!init_map_and_player(game, map_file))
		return (0);
	game->current_weapon = RAYGUN;
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
