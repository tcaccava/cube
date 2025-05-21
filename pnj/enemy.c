/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:39:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/21 22:29:51 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int enemy_sees_you(t_enemy *enemy, t_player *player, t_map *map)
{
	double dx;
	double dy;
	double angle_to_player;
	double delta_angle;
	double fov;

	// Calculate direction to player
	dx = player->x / TILE_SIZE - enemy->x;
	dy = player->y / TILE_SIZE - enemy->y;
	angle_to_player = atan2(dy, dx);
	delta_angle = normalize_angle(angle_to_player - enemy->angle);
	fov = M_PI ; // Wider FOV for better detection
	if (fabs(delta_angle) < fov / 2)
	{
		if (line_of_sight(enemy->x, enemy->y, player->x / TILE_SIZE, player->y / TILE_SIZE, map))
			return (1);
	}
	return (0);
}

int line_of_sight(double ex, double ey, double px, double py, t_map *map)
{
	double dx;
	double dy;
	double distance;
	double step_x;
	double step_y;
	double x;
	double y;
	double traveled;
	int map_x;
	int map_y;

	dx = px - ex;
	dy = py - ey;
	distance = sqrt(dx * dx + dy * dy);
	step_x = (dx / distance) * STEP_SIZE;
	step_y = (dy / distance) * STEP_SIZE;
	x = ex;
	y = ey;
	traveled = 0.0;
	while (traveled < distance)
	{
		map_x = (int)x;
		map_y = (int)y;
		// 1) Controllo limiti della mappa, NON DISPLAY_...
		if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
			return (0);
		// 2) Se incontro un muro nella matrice
		if (map->matrix[map_y][map_x] == '1')
			return (0);
		// 3) Avanzo lungo il vettore verso il player
		x += step_x;
		y += step_y;
		traveled += STEP_SIZE;
	}
	// Non ho incontrato ostacoli
	return (1);
}
void update_enemy(t_enemy *enemy, t_player *player, t_map *map)
{
	double dx = player->x / TILE_SIZE - enemy->x;
	double dy = player->y / TILE_SIZE - enemy->y;
	double distance = sqrt(dx * dx + dy * dy);

	if (enemy->health <= 0)
	{
		enemy->state = DEAD;
		return;
	}
	if (enemy->state == IDLE)
		idle(enemy, player, map, dx, dy, distance);
	else if (enemy->state == SEARCH)
		search(enemy, player, map, dx, dy, distance);
	else if (enemy->state == SHOOT)
		shoot(enemy, player, map, dx, dy, distance);
	else if (enemy->state == MELEE)
		melee(enemy, player, map, dx, dy, distance);
}
void idle(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
	double move_x, move_y, speed = 0.03;
	int next_x, next_y;

	(void)dx;
	(void)dy;
	(void)d;
	move_x = cos(e->angle) * speed;
	move_y = sin(e->angle) * speed;
	next_x = (int)(e->x + move_x);
	next_y = (int)(e->y + move_y);
	if (next_x >= 0 && next_x < m->width && next_y >= 0 && next_y < m->height &&
		m->matrix[next_y][next_x] != '1')
	{
		e->x += move_x;
		e->y += move_y;
	}
	else
	{
		e->angle += ((rand() % 60) - 30) * M_PI / 180;
		e->angle = normalize_angle(e->angle);
	}
	if (enemy_sees_you(e, p, m))
	{
		e->state = SEARCH;
		e->sees_player = 1;
	}
}
void shoot(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
	double angle_to_player;

	if (!enemy_sees_you(e, p, m))
	{
		e->state = SEARCH;
		e->sees_player = 0;
		return;
	}
	if (d >= 6.0)
	{
		e->state = SEARCH;
		return;
	}
	if (d < 1.5)
	{
		e->state = MELEE;
		e->cooldown = 0;
		return;
	}
	angle_to_player = atan2(dy, dx);
	e->angle = angle_to_player;
	if (e->cooldown <= 0)
	{
		p->health -= 10;
		e->cooldown = 30;
	}
	else
		e->cooldown--;
}

void search(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
	double move_x, move_y, speed = 0.05, angle_to_player;
	int next_x, next_y;

	if (!enemy_sees_you(e, p, m))
	{
		e->state = IDLE;
		e->sees_player = 0;
		return;
	}
	if (d < 1.5)
	{
		e->state = MELEE;
		e->cooldown = 0;
		return;
	}
	if (d < 6)
	{
		e->state = SHOOT;
		e->cooldown = 0;
		return;
	}
	angle_to_player = atan2(dy, dx);
	e->angle = angle_to_player;
	move_x = cos(e->angle) * speed;
	move_y = sin(e->angle) * speed;
	next_x = (int)(e->x + move_x);
	next_y = (int)(e->y + move_y);
	if (next_x >= 0 && next_x < m->width && next_y >= 0 && next_y < m->height &&
		m->matrix[next_y][next_x] != '1')
	{
		e->x += move_x;
		e->y += move_y;
	}
}
void melee(t_enemy *e, t_player *p, t_map *m, double dx, double dy, double d)
{
	double angle_to_player;

	if (!enemy_sees_you(e, p, m) || d >= 1.5)
	{
		e->state = SEARCH;
		return;
	}
	angle_to_player = atan2(dy, dx);
	e->angle = angle_to_player;
	if (e->cooldown <= 0)
	{
		p->health -= 25;
		e->cooldown = 30;
	}
	else
		e->cooldown--;
}

void render_enemy(t_game *game, t_enemy *enemy)
{
	if (enemy->state == DEAD)
		return;
	float dx = enemy->x * TILE_SIZE - game->player.x;
	float dy = enemy->y * TILE_SIZE - game->player.y;
	float inv_det = 1.0f / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);

	float transform_x = inv_det * (game->player.dir_y * dx - game->player.dir_x * dy);
	float transform_y = inv_det * (-game->player.plane_y * dx + game->player.plane_x * dy);

	/* 1) dietro la camera o troppo vicino */
	if (transform_y <= 0.2f)
		return;

	/* 2) proietta orizzontalmente */
	int screen_x = (int)((DISPLAY_WIDTH / 2) * (1 + transform_x / transform_y));

	/* 3) occlusione muro: se muro più vicino, skip */
	/* 3) occlusione muro con multi‑sampling */
	if (screen_x < 0 || screen_x >= DISPLAY_WIDTH)
		return;

	/* calcola dimensioni e limiti orizzontali sprite */
	int sprite_size = (int)((TILE_SIZE / transform_y) * ((DISPLAY_WIDTH / 2) / tan(game->player.fov / 2.0f)));
	if (sprite_size > DISPLAY_HEIGHT)
		sprite_size = DISPLAY_HEIGHT;
	int draw_x = screen_x - sprite_size / 2;
	int x0 = draw_x < 0 ? 0 : draw_x;
	int x1 = draw_x + sprite_size - 1;
	if (x1 >= DISPLAY_WIDTH)
		x1 = DISPLAY_WIDTH - 1;

	/* multi‑sampling: 5 campioni equidistanti */
	int samples = 15;
	int visible = 0;
	for (int s = 0; s < samples; s++)
	{
		int col = x0 + s * (x1 - x0) / (samples - 1);
		if (transform_y < game->depth_buffer[col])
			visible++;
	}
	/* se nessun campione è visibile, skip */
	if (visible == 0)
		return;
	/* ora sprite è visibile, procedi col draw */

	/* 4) calcola dimensione sprite */
	sprite_size = (int)((TILE_SIZE / transform_y) * ((DISPLAY_WIDTH / 2) / tan(game->player.fov / 2.0f)));
	if (sprite_size > DISPLAY_HEIGHT)
		sprite_size = DISPLAY_HEIGHT;

	/* 5) posizioni di draw */
	draw_x = screen_x - sprite_size / 2;
	int y_offset = sprite_size / 6;
	int draw_y = (DISPLAY_HEIGHT - sprite_size) / 2 + game->pitch + y_offset;

	/* 6) disegna */
	draw_enemy_sprite(game, enemy->texture, (t_point){draw_x, draw_y}, sprite_size);
}

void draw_enemy_sprite(t_game *game, t_img *sprite, t_point pos, int size)
{
	int i;
	int j;
	int src_x;
	int src_y;
	char *src;
	unsigned int color;
	int x;
	int y;
	char *dst;

	// Protezione base
	if (!sprite || !sprite->addr || size <= 0)
		return;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			// 1) Mappatura texture
			src_x = i * sprite->width / size;
			src_y = j * sprite->height / size;
			// clamp
			if (src_x < 0)
				src_x = 0;
			else if (src_x >= sprite->width)
				src_x = sprite->width - 1;
			if (src_y < 0)
				src_y = 0;
			else if (src_y >= sprite->height)
				src_y = sprite->height - 1;
			// 2) Leggi pixel
			src = sprite->addr + src_y * sprite->line_length + src_x * (sprite->bits_per_pixel / 8);
			color = *(unsigned int *)src;
			// 3) Trasparenza
			if ((color & 0x00FFFFFF) <= 0x0A0A0A)
			{
				j++;
				continue;
			}
			// 4) Posizione sullo schermo
			x = pos.x + i;
			y = pos.y + j;
			// 5) Clipping
			if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT)
			{
				j++;
				continue;
			}
			// 6) Disegna
			dst = game->screen.addr + y * game->screen.line_length + x * (game->screen.bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}
void update_camera_vectors(t_player *player)
{
	double fov_half;

	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	fov_half = player->fov / 2.0;
	player->plane_x = -sin(player->angle) * tan(fov_half);
	player->plane_y = cos(player->angle) * tan(fov_half);
}

void damage_enemy_at_position(t_game *game, double x, double y, int damage)
{
	int i;
	double dx, dy, dist;

	i = 0;
	while (i < game->num_enemies)
	{
		t_enemy *e = &game->enemies[i];
		if (e->state != DEAD)
		{
			dx = e->x - x;
			dy = e->y - y;
			dist = sqrt(dx * dx + dy * dy);
			if (dist < 0.5)
			{
				e->health -= damage;
				if (e->health <= 0)
					e->state = DEAD;
				return;
			}
		}
		i++;
	}
}
