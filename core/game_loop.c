/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:17:11 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:25:23 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static void	update_all_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].active)
			update_enemy(&game->enemies[i], &game->player, &game->map);
		i++;
	}
}

static void	cast_all_rays(t_game *game)
{
	int		i;
	double	ray_offset;
	double	radiant_angle;

	i = 0;
	while (i < DISPLAY_WIDTH)
	{
		ray_offset = game->player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
		radiant_angle = normalize_angle(game->player.angle + ray_offset);
		game->rays[i].radiant_angle = radiant_angle;
		game->rays[i].player_angle = game->player.angle;
		game->rays[i].distance = ray_casting(game, radiant_angle, i);
		game->depth_buffer[i] = game->rays[i].distance * cos(radiant_angle
				- game->player.angle);
		i++;
	}
}

static void	weapon_animation(t_game *game, int *anim_frames)
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

int	render_next_frame(t_game *game)
{
	static int	anim_frames;

	move_player(&game->player);
	update_all_enemies(game);
	cast_all_rays(game);
	weapon_animation(game, &anim_frames);
	render_scene(game);
	render_next_frame_enemies(game);
	draw_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.ptr, 0, 0);
	render_ui(game);
	return (0);
}
