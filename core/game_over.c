/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:48:53 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/09 02:40:14 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	check_player_death(t_game *game)
{
	if (game->player.health <= 0)
	{
		game->game_over = 1;
		game->game_over_timer = 0;
	}
}

void	load_game_over_image(t_game *game)
{
	game->game_over_img = mlx_xpm_file_to_image(game->mlx,
			"texture/game_over.xpm", &game->game_over_width,
			&game->game_over_height);
	if (!game->game_over_img)
	{
		printf("Error: Could not load game_over.xpm\n");
		game->game_over_img = NULL;
	}
}

void	game_over_screen(t_game *game)
{
	int	center_x;
	int	center_y;
	int	y;
	int	x;

	if (!game->game_over_img)
	{
		y = -1;
		while (++y < DISPLAY_HEIGHT)
		{
			x = -1;
			while (++x < DISPLAY_WIDTH)
				mlx_pixel_put(game->mlx, game->win, x, y, 0x000000);
		}
		return ;
	}
	center_x = (DISPLAY_WIDTH - game->game_over_width) / 2;
	center_y = (DISPLAY_HEIGHT - game->game_over_height) / 2;
	if (center_x < 0)
		center_x = 0;
	if (center_y < 0)
		center_y = 0;
	mlx_put_image_to_window(game->mlx, game->win, game->game_over_img, center_x,
		center_y);
}
