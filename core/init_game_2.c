/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:18 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:33:19 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	init_standard_mode(t_game *game, char **argv)
{
	int	valid;

	valid = check_file_cub(argv[1]);
	if (valid == 0)
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
	int				valid;

	valid = check_file_cub(argv[1]);
	if (valid == 0)
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

void	init_player(t_player *player)
{
	init_player_basics(player);
	init_player_weapons(player);
}
