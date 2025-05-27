/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:03:13 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:25:46 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	load_all_textures(t_game *game)
{
	if (!load_basic_textures(game))
		return (0);
	if (!load_door_textures(game))
		return (0);
	if (!load_special_textures(game))
		return (0);
	return (1);
}
