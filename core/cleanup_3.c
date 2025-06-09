/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:22:02 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/09 18:00:46 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	cleanup_screen_and_ui(t_game *game)
{
	if (game->screen.ptr)
		mlx_destroy_image(game->mlx, game->screen.ptr);
	if (game->game_over_img)
		mlx_destroy_image(game->mlx, game->game_over_img);
}

void	cleanup_map_textures(t_game *game)
{
	t_img	*t[13];
	int		i;

	t[0] = &game->map.north;
	t[1] = &game->map.south;
	t[2] = &game->map.east;
	t[3] = &game->map.west;
	t[4] = &game->map.wall_texture;
	t[5] = &game->map.floor_texture;
	t[6] = &game->map.enemy_texture;
	t[7] = &game->map.wall_portal_texture;
	t[8] = &game->map.door_texture;
	t[9] = &game->map.open_door_texture;
	t[10] = &game->map.open_door_shooted_texture;
	t[11] = &game->map.door_shooted_texture;
	t[12] = &game->map.wall_shooted_texture;
	i = 0;
	while (i < 13)
	{
		if (t[i]->ptr)
			mlx_destroy_image(game->mlx, t[i]->ptr);
		i++;
	}
}

void	cleanup_map_matrix(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.matrix)
	{
		while (game->map.matrix[i])
		{
			free(game->map.matrix[i]);
			i++;
		}
		free(game->map.matrix);
	}
}

void	cleanup_healgun(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->healgun_frames[i].ptr)
			mlx_destroy_image(game->mlx, game->healgun_frames[i].ptr);
		i++;
	}
}

void	cleanup_entities(t_game *game)
{
	int	i;

	free(game->enemies);
	i = 0;
	while (i < game->num_weapon_pickup)
	{
		if (game->weapon_pickup[i].sprite.ptr)
			mlx_destroy_image(game->mlx, game->weapon_pickup[i].sprite.ptr);
		i++;
	}
	free(game->weapon_pickup);
	i = 0;
	while (i < game->num_open_doors)
	{
		if (game->open_doors[i].sprite.ptr)
			mlx_destroy_image(game->mlx, game->open_doors[i].sprite.ptr);
		i++;
	}
	free(game->open_doors);
}
