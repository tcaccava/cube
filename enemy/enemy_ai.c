/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:09 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:10 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	idle(t_enemy *e, t_player *p, t_map *m)
{
	double	move_x;
	double	move_y;
	double	speed;
	int		next_pos[2];

	(void)p;
	speed = 1.5;
	move_x = cos(e->angle) * speed;
	move_y = sin(e->angle) * speed;
	next_pos[0] = (int)((e->x + move_x) / TILE_SIZE);
	next_pos[1] = (int)((e->y + move_y) / TILE_SIZE);
	if (next_pos[0] >= 0 && next_pos[0] < m->width && next_pos[1]
		>= 0 && next_pos[1] < m->height && m->matrix[next_pos[1]]
		[next_pos[0]] != '1')
	{
		e->x += move_x;
		e->y += move_y;
	}
	else
		apply_random_rotation(e);
	if (enemy_sees_you(e, p, m))
		set_search_state(e);
}

void	search(t_enemy *e, t_player *p, t_map *m)
{
	double	dx;
	double	dy;
	double	d;
	double	distance_in_tiles;

	dx = p->x - e->x;
	dy = p->y - e->y;
	d = sqrt(dx * dx + dy * dy);
	distance_in_tiles = d / TILE_SIZE;
	if (!enemy_sees_you(e, p, m))
	{
		e->state = IDLE;
		e->sees_player = 0;
		return ;
	}
	if (distance_in_tiles < 1.5)
		set_melee_state(e);
	else if (distance_in_tiles < 6)
		set_shoot_state(e);
	else
		move_towards_player(e, p, m, atan2(dy, dx));
}

static void	handle_shoot_distance(t_enemy *e, t_player *p,
		double distance_in_tiles, t_point direction)
{
	if (distance_in_tiles >= 6.0)
	{
		e->state = SEARCH;
		return ;
	}
	if (distance_in_tiles < 1.5)
		set_melee_state(e);
	else
	{
		e->angle = atan2(direction.y, direction.x);
		handle_shoot_cooldown(e, p);
	}
}

void	shoot(t_enemy *e, t_player *p, t_map *m)
{
	double	dx;
	double	dy;
	double	d;
	double	distance_in_tiles;

	dx = p->x - e->x;
	dy = p->y - e->y;
	d = sqrt(dx * dx + dy * dy);
	distance_in_tiles = d / TILE_SIZE;
	if (!enemy_sees_you(e, p, m))
	{
		e->state = SEARCH;
		e->sees_player = 0;
		return ;
	}
	handle_shoot_distance(e, p, distance_in_tiles, (t_point){dx, dy});
}

void	melee(t_enemy *e, t_player *p, t_map *m)
{
	double	dx;
	double	dy;
	double	d;
	double	distance_in_tiles;

	dx = p->x - e->x;
	dy = p->y - e->y;
	d = sqrt(dx * dx + dy * dy);
	distance_in_tiles = d / TILE_SIZE;
	if (!enemy_sees_you(e, p, m) || distance_in_tiles >= 1.5)
	{
		e->state = SEARCH;
		return ;
	}
	e->angle = atan2(dy, dx);
	handle_melee_cooldown(e, p);
}
