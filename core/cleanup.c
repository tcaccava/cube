/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:28:29 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/09 17:54:27 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	cleanup_sprite_array(t_game *game, t_img *sprites, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (sprites[i].ptr)
		{
			mlx_destroy_image(game->mlx, sprites[i].ptr);
			sprites[i].ptr = NULL;
		}
		i++;
	}
}

void	cleanup_shared_sprites(t_game *game)
{
	cleanup_sprite_array(game, game->shared_walk_sprites, 2);
	cleanup_sprite_array(game, game->shared_shoot_sprites, 2);
	cleanup_sprite_array(game, game->shared_death_sprites, 3);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_shared_sprites(game);
	cleanup_entities(game);
	cleanup_weapons(game);
	cleanup_healgun(game);
	cleanup_screen_and_ui(game);
	cleanup_map_textures(game);
	cleanup_map_matrix(game);
	cleanup_mlx(game);
}

static int	is_already_destroyed(t_cleanup_helper *helper, void *ptr)
{
	helper->k = 0;
	while (helper->k < helper->destroyed_count)
	{
		if (helper->destroyed[helper->k] == ptr)
			return (1);
		helper->k++;
	}
	return (0);
}

void	cleanup_weapons(t_game *game)
{
	t_cleanup_helper	helper;
	void				*ptr;

	helper = (t_cleanup_helper){0};
	helper.i = -1;
	while (++helper.i < MAX_WEAPONS)
	{
		helper.j = -1;
		while (++helper.j < 3)
		{
			ptr = (void *)game->weapons[helper.i][helper.j].ptr;
			if (ptr && !is_already_destroyed(&helper, ptr))
			{
				mlx_destroy_image(game->mlx,
					game->weapons[helper.i][helper.j].ptr);
				helper.destroyed[helper.destroyed_count++] = ptr;
			}
			game->weapons[helper.i][helper.j].ptr = NULL;
		}
	}
}
