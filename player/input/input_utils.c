/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:19:46 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:47 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	switch_to_next_weapon(t_game *game)
{
	int	next_weapon;

	next_weapon = (game->current_weapon + 1) % MAX_WEAPONS;
	while (!game->player.has_weapon[next_weapon]
		&& next_weapon != game->current_weapon)
	{
		next_weapon = (next_weapon + 1) % MAX_WEAPONS;
	}
	if (game->player.has_weapon[next_weapon])
	{
		game->current_weapon = next_weapon;
		game->player.current_weapon = next_weapon;
		printf("✅ Arme changée : %d\n", next_weapon);
	}
}

void	switch_to_previous_weapon(t_game *game)
{
	int	prev_weapon;

	prev_weapon = (game->current_weapon - 1 + MAX_WEAPONS) % MAX_WEAPONS;
	while (!game->player.has_weapon[prev_weapon]
		&& prev_weapon != game->current_weapon)
		prev_weapon = (prev_weapon - 1 + MAX_WEAPONS) % MAX_WEAPONS;
	if (game->player.has_weapon[prev_weapon])
	{
		game->current_weapon = prev_weapon;
		game->player.current_weapon = prev_weapon;
		printf("✅ Arme changée : %d\n", prev_weapon);
	}
}
