/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_core_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:37:07 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:19:57 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	update_camera_vectors(t_player *player)
{
	double	fov_half;

	fov_half = player->fov / 2.0;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * tan(fov_half);
	player->plane_y = cos(player->angle) * tan(fov_half);
}

void	update_enemy(t_enemy *enemy, t_player *player, t_map *map)
{
	t_enemy_ctx	ctx;

	ctx.enemy = enemy;
	ctx.player = player;
	ctx.map = map;
	ctx.dx = player->x - enemy->x;
	ctx.dy = player->y - enemy->y;
	ctx.distance = sqrt(ctx.dx * ctx.dx + ctx.dy * ctx.dy);
	if (enemy->health <= 0)
	{
		enemy->state = DEAD;
		return ;
	}
	if (enemy->state == IDLE)
		idle(&ctx);
	else if (enemy->state == SEARCH)
		search(&ctx);
	else if (enemy->state == SHOOT)
		shoot(&ctx);
	else if (enemy->state == MELEE)
		melee(&ctx);
}

int	damage_enemy_at_position(t_game *game, int tx, int ty, int dmg)
{
	t_enemy	*e;
	int		i;

	i = 0;
	while (i < game->num_enemies)
	{
		e = &game->enemies[i];
		if ((int)(e->x / TILE_SIZE) == tx && (int)(e->y / TILE_SIZE) == ty
			&& e->active)
		{
			e->health -= dmg;
			if (e->health <= 0)
			{
				e->death_timer = 300;
				e->animation.current_frame = 0;
				e->animation.frame_counter = 0;
				e->state = DEAD;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
