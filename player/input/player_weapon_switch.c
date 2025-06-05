/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_weapon_switch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:19:52 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 17:02:49 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	handle_weapon_keys_press(int keycode, t_player *player)
{
	if (keycode == 48)
		switch_to_hands(player);
	if (keycode == 49)
		switch_to_raygun(player);
	if (keycode == 50)
		switch_to_portalgun(player);
	if (keycode == 51)
		switch_to_healgun(player);
}

void	switch_to_hands(t_player *player)
{
	if (player->has_weapon[HANDS])
	{
		player->current_weapon = HANDS;
		if (player->game)
			player->game->current_weapon = HANDS;
	}
}

void	switch_to_raygun(t_player *player)
{
	if (player->has_weapon[RAYGUN])
	{
		player->current_weapon = RAYGUN;
		if (player->game)
			player->game->current_weapon = RAYGUN;
	}
}

void	switch_to_portalgun(t_player *player)
{
	if (player->has_weapon[PORTALGUN])
	{
		player->current_weapon = PORTALGUN;
		if (player->game)
			player->game->current_weapon = PORTALGUN;
	}
}

void	switch_to_healgun(t_player *player)
{
	if (player->has_weapon[HEALGUN])
	{
		player->current_weapon = HEALGUN;
		if (player->game)
			player->game->current_weapon = HEALGUN;
	}
}
