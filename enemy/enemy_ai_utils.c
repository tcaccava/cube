/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:07 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:08 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	apply_random_rotation(t_enemy *e)
{
	e->angle += ((rand() % 60) - 30) * M_PI / 180;
	e->angle = normalize_angle(e->angle);
}

void	set_search_state(t_enemy *e)
{
	e->state = SEARCH;
	e->sees_player = 1;
}

void	set_melee_state(t_enemy *e)
{
	e->state = MELEE;
	e->cooldown = 0;
}

void	set_shoot_state(t_enemy *e)
{
	e->state = SHOOT;
	e->cooldown = 0;
}

void	move_towards_player(t_enemy *e, t_player *p, t_map *m, double angle)
{
	double	move_x;
	double	move_y;
	int		next_pos[2];

	(void)p;
	e->angle = angle;
	move_x = cos(e->angle) * 3.0;
	move_y = sin(e->angle) * 3.0;
	next_pos[0] = (int)((e->x + move_x) / TILE_SIZE);
	next_pos[1] = (int)((e->y + move_y) / TILE_SIZE);
	if (next_pos[0] >= 0 && next_pos[0] < m->width && next_pos[1] >= 0
		&& next_pos[1] < m->height && m->matrix[next_pos[1]]
		[next_pos[0]] != '1')
	{
		e->x += move_x;
		e->y += move_y;
	}
}
