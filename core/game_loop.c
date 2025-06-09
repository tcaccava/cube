/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:20 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/09 18:11:51 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_next_frame_weapons(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_weapon_pickup)
	{
		if (game->weapon_pickup[i].active)
			render_weapon_pickup(game, &game->weapon_pickup[i]);
		i++;
	}
}

int	loop_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press_wrapper, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win, mouse_button, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_loop(game->mlx);
	return (0);
}

void	weapon_animation(t_game *game, int *anim_frames)
{
	if (game->player.weapon.is_firing)
	{
		(*anim_frames)++;
		if (*anim_frames > 11)
		{
			game->player.weapon.is_firing = 0;
			game->player.weapon.current_state = WEAPON_NEUTRE;
			game->player.weapon.frame = 0;
			*anim_frames = 0;
		}
	}
	else
		*anim_frames = 0;
	if (game->player.fire_cooldown > 0)
		game->player.fire_cooldown--;
}
