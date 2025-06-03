/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:56 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:57 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	apply_damage_effect(unsigned int color, unsigned int *damaged_color)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red = (int)(red * 0.7);
	green = (int)(green * 0.7);
	blue = (int)(blue * 0.7);
	*damaged_color = (red << 16) | (green << 8) | blue;
}
