/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:26 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/09 05:04:12 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		printf("Usage: %s <scene.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_cub_file(argv[1], &game))
		return (1);
	game.game_over = 0;
	load_game_over_image(&game);
	init_rays(&game);
	loop_game(&game);
	cleanup_game(&game);
	return (0);
}
