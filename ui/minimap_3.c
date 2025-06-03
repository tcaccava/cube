/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:02 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:17:03 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	minimap(t_game *game)
{
	if (!game->minimap.show)
		return ;
	draw_minimap_background(game);
	draw_minimap_cells(game);
	draw_minimap_player(game);
}
