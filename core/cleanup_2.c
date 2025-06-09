/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:19:07 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/09 17:54:15 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	cleanup_mlx(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	cleanup_scene(t_scene_data *scene)
{
	if (scene->north_texture)
	{
		free(scene->north_texture);
		scene->north_texture = NULL;
	}
	if (scene->south_texture)
	{
		free(scene->south_texture);
		scene->south_texture = NULL;
	}
	if (scene->west_texture)
	{
		free(scene->west_texture);
		scene->west_texture = NULL;
	}
	if (scene->east_texture)
	{
		free(scene->east_texture);
		scene->east_texture = NULL;
	}
}

int	key_press_wrapper(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	return (key_press(keycode, &game->player));
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
	return (0);
}
