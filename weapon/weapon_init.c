/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:13 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:14 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_player_weapons(t_player *player)
{
	init_weapon_inventory(player);
	init_weapon_state(player);
	init_weapon_ammo(player);
}

void	init_weapon_inventory(t_player *player)
{
	player->has_weapon[HANDS] = true;
	player->has_weapon[RAYGUN] = false;
	player->has_weapon[PORTALGUN] = false;
	player->has_weapon[HEALGUN] = false;
	player->current_weapon = HANDS;
}

void	init_weapon_state(t_player *player)
{
	player->weapon.current_state = WEAPON_NEUTRE;
	player->weapon.frame = 0;
	player->weapon.frame_delay = 0;
	player->weapon.is_firing = 0;
	player->fire_cooldown = 0;
}

void	init_weapon_ammo(t_player *player)
{
	player->healgun_ammo = 0;
	player->healgun_is_loaded = 0;
	player->healgun_animating = 0;
	player->healgun_anim_frame = 0;
	player->healgun_anim_timer = 0;
}

int	load_all_weapons(t_game *game)
{
	if (!load_hands(game))
		return (0);
	if (!load_raygun(game))
		return (0);
	if (!load_portalgun(game))
		return (0);
	if (!load_healgun(game))
		return (0);
	return (1);
}
