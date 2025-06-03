/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heal_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:21:15 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:21:16 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	use_healgun(t_game *game)
{
	if (!validate_healgun_use(game))
	{
		printf("❌ Heal Gun vide !\n");
		return ;
	}
	start_heal_process(game);
	consume_heal_ammo(game);
	apply_healing(game);
	check_reload_healgun(game);
}

int	validate_healgun_use(t_game *game)
{
	if (!game->player.healgun_is_loaded)
		return (0);
	if (game->player.healgun_ammo <= 0)
		return (0);
	return (1);
}

void	start_heal_process(t_game *game)
{
	game->player.healgun_animating = 1;
	game->player.healgun_anim_frame = 0;
	game->player.healgun_anim_timer = 10;
}

void	consume_heal_ammo(t_game *game)
{
	game->player.healgun_ammo--;
	game->player.healgun_is_loaded = 0;
}

void	apply_healing(t_game *game)
{
	game->player.health = 100;
	printf("💉 Heal Gun utilisé ! Santé: %d, Munitions: %d\n",
		game->player.health, game->player.healgun_ammo);
}
