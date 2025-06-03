/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:05 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:06 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_next_frame_enemies(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->num_enemies)
	{
		if (game->enemies[j].active)
			render_enemy(game, &game->enemies[j]);
		j++;
	}
}
