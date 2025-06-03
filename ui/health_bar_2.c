/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:16:58 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:59 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_health_bar(t_game *game)
{
	draw_health_bar_border(game);
	draw_health_bar_background(game);
	draw_health_bar_fill(game);
}
