/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:29 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:15:30 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	mouse_button(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (game->map.north.ptr != NULL)
		return (0);
	if (button == 1)
		handle_left_click(game);
	else if (button == 4 || button == 5)
		handle_scroll_wheel(game, button);
	else if (button == 3 && game->current_weapon == PORTALGUN)
		remove_all_portals(game);
	return (0);
}

void	handle_left_click(t_game *game)
{
	if (game->current_weapon == HANDS)
		return ;
	if (game->current_weapon == RAYGUN)
		shoot_raygun(game);
	else if (game->current_weapon == PORTALGUN)
		shoot_portalgun(game);
	else if (game->current_weapon == HEALGUN)
		use_healgun(game);
}

void	shoot_raygun(t_game *game)
{
	if (!game->player.weapon.is_firing)
	{
		game->player.weapon.is_firing = 1;
		game->player.weapon.current_state = WEAPON_PREFIRE;
		game->player.weapon.frame = 1;
		game->player.weapon.frame_delay = 10;
		calculate_shoot(game);
	}
}

void	shoot_portalgun(t_game *game)
{
	if (game->portal_count < 2)
		calculate_shoot(game);
}

void	shoot_healgun(t_game *game)
{
	if (!game->player.healgun_is_loaded)
	{
		printf("Heal Gun empty! Find ammo.\n");
		return ;
	}
	if (game->player.healgun_ammo <= 0)
	{
		printf("No ammo!\n");
		return ;
	}
	use_healgun(game);
	start_healgun_animation(game);
}
