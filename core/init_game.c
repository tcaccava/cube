/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:43:46 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/26 20:46:48 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT,
			"Raycaster");
	mlx_mouse_hide(game->mlx, game->win);
	if (!game->win)
		return (0);
	game->screen.ptr = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game->screen.ptr)
		return (0);
	game->screen.addr = mlx_get_data_addr(game->screen.ptr,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
	return (1);
}

int	init_map_and_player(t_game *game, char *map_file)
{
	if (!read_map(map_file, game))
		return (0);
	if (!set_player_pos(game))
	{
		printf("Erreur: Aucune position de départ trouvée dans la carte!\n");
		return (0);
	}
	return (1);
}

void	init_portals(t_game *game)
{
	game->portal_1.is_active = 0;
	game->portal_2.is_active = 0;
	game->portal_count = 0;
}

void	init_ui_components(t_game *game)
{
	init_minimap(game);
	init_health_bar(game);
}

int	init_game(t_game *game, char *map_file)
{
	init_player(&game->player);
	game->player.game = game;
	if (!init_mlx_window(game))
		return (0);
	if (!init_map_and_player(game, map_file))
		return (0);
	game->current_weapon = PORTALGUN;
	if (!load_all_textures(game))
		return (0);
	if (!load_all_weapons(game))
		return (0);
	if (!init_all_enemies(game))
		return (0);
	init_portals(game);
	init_ui_components(game);
	return (1);
}
