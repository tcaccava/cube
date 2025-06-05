/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:26 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 17:15:45 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <scene.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_cub_file(argv[1], &game))
		return (1);
	init_rays(&game);
	loop_game(&game);
	return (0);
}
