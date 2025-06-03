/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_raygun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:28 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:17:29 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	handle_raygun_shot(t_game *game, t_ray *center_ray)
{
	if (check_enemy_hit(game, center_ray))
		return ;
	apply_wall_damage(game, center_ray);
}

int	check_enemy_hit(t_game *game, t_ray *center_ray)
{
	t_shoot_params	params;
	int				i;

	params.player_x = game->player.x;
	params.player_y = game->player.y;
	params.ray_dir_x = cos(game->player.angle);
	params.ray_dir_y = sin(game->player.angle);
	params.center_ray = center_ray;
	i = 0;
	while (i < game->num_enemies)
	{
		params.enemy = &game->enemies[i];
		if (is_enemy_in_line_of_fire(game, &params))
			return (damage_enemy(&game->enemies[i], game));
		i++;
	}
	return (0);
}

void	shoot_raygun(t_game *game)
{
	if (!game->player.weapon.is_firing)
	{
		start_raygun_animation(game);
		calculate_shoot(game);
	}
}

void	start_raygun_animation(t_game *game)
{
	game->player.weapon.is_firing = 1;
	game->player.weapon.current_state = WEAPON_PREFIRE;
	game->player.weapon.frame = 1;
	game->player.weapon.frame_delay = 10;
}
