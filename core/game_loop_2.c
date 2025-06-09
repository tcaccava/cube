/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:16 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/09 18:12:17 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	handle_game_over(t_game *game, t_frame_data *data)
{
	game_over_screen(game);
	data->game_over_timer++;
	if (data->game_over_timer > 3600)
	{
		cleanup_game(game);
		exit(0);
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

static void	render_game_elements(t_game *game, t_frame_data *data)
{
	update_healgun_animation(game);
	cast_all_rays(game);
	weapon_animation(game, &data->anim_frames);
	render_scene(game);
	render_next_frame_enemies(game);
	render_next_frame_weapons(game);
	draw_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.ptr, 0, 0);
	render_ui(game);
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

int	render_next_frame(t_game *game)
{
	static t_frame_data	data = {0};

	move_player(&game->player);
	update_all_enemies(game);
	check_player_death(game);
	if (game->game_over)
	{
		handle_game_over(game, &data);
		return (0);
	}
	render_game_elements(game, &data);
	return (0);
}
