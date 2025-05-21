/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:43:09 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/21 20:53:24 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	render_next_frame(t_game *game)
{
	int			i;
	double		ray_offset;
	double		radiant_angle;
	static int	anim_frames = 0;
	int			j;

	move_player(&game->player);
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].active)
			update_enemy(&game->enemies[i], &game->player, &game->map);
		i++;
	}
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
	if (game->player.weapon.is_firing)
	{
		anim_frames++;
		if (anim_frames > 11)
		{
			game->player.weapon.is_firing = 0;
			game->player.weapon.current_state = WEAPON_NEUTRE;
			game->player.weapon.frame = 0;
			anim_frames = 0;
		}
	}
	else
	{
		anim_frames = 0;
	}
	if (game->player.fire_cooldown > 0)
		game->player.fire_cooldown--;
	render_scene(game);
	j = 0;
	while (j < game->num_enemies)
	{
		if (game->enemies[j].active)
			render_enemy(game, &game->enemies[j]);
		j++;
	}
	draw_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.ptr, 0, 0);
	render_ui(game);
	return (0);
}

void	render_scene(t_game *game)
{
	int	col;

	col = 0;
	while (col < DISPLAY_WIDTH)
	{
		render_column(game, col, &game->rays[col]);
		col++;
	}
}

void	render_ui(t_game *game)
{
	render_weapon(game);
	draw_health_bar(game);
	minimap(game);
}

int	loop_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
	mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win, mouse_button, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_loop(game->mlx);
	return (0);
}
