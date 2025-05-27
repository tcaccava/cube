/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:02:41 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 19:32:01 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	move_idle(t_enemy *e, t_map *m)
{
	double	speed;
	double	move_x;
	double	move_y;
	int		next_x;
	int		next_y;

	speed = 1.5;
	move_x = cos(e->angle) * speed;
	move_y = sin(e->angle) * speed;
	next_x = (int)((e->x + move_x) / TILE_SIZE);
	next_y = (int)((e->y + move_y) / TILE_SIZE);
	if (next_x >= 0 && next_x < m->width && next_y >= 0 && next_y < m->height
		&& m->matrix[next_y][next_x] != '1')
	{
		e->x += move_x;
		e->y += move_y;
	}
	else
	{
		e->angle += ((rand() % 60) - 30) * M_PI / 180;
		e->angle = normalize_angle(e->angle);
	}
}

void	idle(t_enemy_ctx *ctx)
{
	move_idle(ctx->enemy, ctx->map);
	if (enemy_sees_you(ctx->enemy, ctx->player, ctx->map))
	{
		ctx->enemy->state = SEARCH;
		ctx->enemy->sees_player = 1;
	}
}

void	search(t_enemy_ctx *ctx)
{
	t_enemy	*e;
	double	move_x;
	double	move_y;
	int		next_x;
	int		next_y;

	e = ctx->enemy;
	move_x = ctx->dx / ctx->distance * 2.0;
	move_y = ctx->dy / ctx->distance * 2.0;
	next_x = (int)((e->x + move_x) / TILE_SIZE);
	next_y = (int)((e->y + move_y) / TILE_SIZE);
	if (next_x >= 0 && next_x < ctx->map->width && next_y >= 0
		&& next_y < ctx->map->height && ctx->map->matrix[next_y][next_x] != '1')
	{
		e->x += move_x;
		e->y += move_y;
	}
	e->angle = atan2(ctx->dy, ctx->dx);
	if (ctx->distance < TILE_SIZE * 1.5)
		e->state = MELEE;
	else if (ctx->distance < TILE_SIZE * 6.0)
		e->state = SHOOT;
}

void	shoot(t_enemy_ctx *ctx)
{
	t_enemy	*e;

	e = ctx->enemy;
	e->angle = atan2(ctx->dy, ctx->dx);
	if (ctx->distance > TILE_SIZE * 6.0)
	{
		e->state = SEARCH;
		return ;
	}
	if (e->cooldown <= 0)
	{
		e->cooldown = 60;
		e->shooting = 1;
	}
	else
	{
		e->cooldown--;
		if (e->cooldown == 30)
			e->shooting = 0;
	}
}

void	melee(t_enemy_ctx *ctx)
{
	t_enemy	*e;

	e = ctx->enemy;
	e->angle = atan2(ctx->dy, ctx->dx);
	if (ctx->distance > TILE_SIZE * 2.0)
	{
		e->state = SEARCH;
		return ;
	}
	if (e->cooldown <= 0)
	{
		ctx->player->health -= 20;
		e->cooldown = 90;
	}
	else
		e->cooldown--;
}
