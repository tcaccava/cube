/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:39:45 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/21 20:59:54 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// void render_pnj(t_game *game)
// {
// //not finish
// }

// void	update_pnj(t_game *game)
// {
// 	double dx = game->pnj.x - game->player.x;
//     double dy = game->pnj.y - game->player.y;
//     game->pnj.distance = sqrt(dx*dx + dy*dy);
// }

// void	init_pnj(t_game *game)
// {
// 	game->pnj.x = 0;
// 	game->pnj.y = 0;
// 	game->pnj.distance = 0;
// 	game->pnj.active = 1;
// 	game->pnj->texture.ptr = mlx_xpm_file_to_image(game->mlx,
//"./texture/pnj.xpm",
//                                                  &width, &height);
// 	if (!game->pnj.texture.ptr)
//     {
//         printf("Erreur: a mettre en anglais mais pas de sprite ennemi
// pnj\n");
//         game->pnj.active = 0;
//         return ;
//     }
//     game->pnj.texture.width = width;
//     game->pnj.texture.height = height;
//     game->pnj.texture.addr = mlx_get_data_addr(game->pnj.texture.ptr,
//                                              &game->pnj.texture.bits_per_pixel,
//                                              &game->pnj.texture.line_length,
//                                              &game->pnj.texture.endian);
// }

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
	fov = M_PI / 3; // Wider FOV for better detection
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
	double dx;
	double dy;
	double distance;
	double speed;
	int next_x;
	int next_y;
	double angle_to_player;
	double move_x;
	double move_y;
	int player_tile_x;
	int player_tile_y;
	int enemy_tile_x;
	int enemy_tile_y;

	if (enemy->health <= 0)
	{
		enemy->state = DEAD;
		return;
	}
	player_tile_x = (int)(player->x / TILE_SIZE);
	player_tile_y = (int)(player->y / TILE_SIZE);
	enemy_tile_x = (int)(enemy->x);
	enemy_tile_y = (int)(enemy->y);
	if (player_tile_x == enemy_tile_x && player_tile_y == enemy_tile_y)
		return;
	dx = player->x / TILE_SIZE - enemy->x;
	dy = player->y / TILE_SIZE - enemy->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 1.0 && enemy->state != MELEE)
	{
		enemy->state = MELEE;
		enemy->cooldown = 0;
		return;
	}
	if (enemy->state == IDLE)
	{
		if (distance < 5.0)
		{
			enemy->state = SEARCH;
			enemy->sees_player = 0;
			return;
		}
		speed = 0.03;
		move_x = cos(enemy->angle) * speed;
		move_y = sin(enemy->angle) * speed;
		next_x = (int)(enemy->x + move_x);
		next_y = (int)(enemy->y + move_y);
		if (next_x >= 0 && next_x < map->width && next_y < map->height && next_y >= 0 && map->matrix[next_y][next_x] != '1')
		{
			enemy->x = enemy->x + move_x;
			enemy->y = enemy->y + move_y;
		}
		else
		{
			enemy->angle = enemy->angle + ((rand() % 60) - 30) * M_PI / 180;
			enemy->angle = normalize_angle(enemy->angle);
		}
		if (enemy_sees_you(enemy, player, map))
		{
			enemy->state = SEARCH;
			enemy->sees_player = 1;
		}
	}
	else if (enemy->state == SEARCH)
	{
		if (!enemy_sees_you(enemy, player, map))
		{
			enemy->state = IDLE;
			enemy->sees_player = 0;
			return;
		}
		if (distance < 1.5)
		{
			enemy->state = MELEE;
			enemy->cooldown = 0;
			return;
		}
		else if (distance < 10)
		{
			enemy->state = SHOOT;
			enemy->cooldown = 0;
			return;
		}
		angle_to_player = atan2(dy, dx);
		enemy->angle = angle_to_player;
		speed = 0.05;
		move_x = cos(enemy->angle) * speed;
		move_y = sin(enemy->angle) * speed;
		next_x = (int)(enemy->x + move_x);
		next_y = (int)(enemy->y + move_y);
		if (next_x >= 0 && next_x < map->width && next_y < map->height && next_y >= 0 && map->matrix[next_y][next_x] != '1')
		{
			enemy->x = enemy->x + move_x;
			enemy->y = enemy->y + move_y;
		}
	}
	else if (enemy->state == SHOOT)
	{
		if (!enemy_sees_you(enemy, player, map))
		{
			enemy->state = SEARCH;
			enemy->sees_player = 0;
			return;
		}
		if (distance >= 6.0)
		{
			enemy->state = SEARCH;
			return;
		}
		if (distance < 1.5)
		{
			enemy->state = MELEE;
			enemy->cooldown = 0;
			return;
		}
		angle_to_player = atan2(dy, dx);
		enemy->angle = angle_to_player;
		// Attack with cooldown
		if (enemy->cooldown <= 0)
		{
			player->health = player->health - 10;
			enemy->cooldown = 30;
		}
		else
			enemy->cooldown--;
	}
	else if (enemy->state == MELEE)
	{
		if (!enemy_sees_you(enemy, player, map) || distance >= 1.5)
		{
			enemy->state = SEARCH;
			return;
		}
		angle_to_player = atan2(dy, dx);
		enemy->angle = angle_to_player;
		if (enemy->cooldown <= 0)
		{
			player->health = player->health - 25;
			enemy->cooldown = 60;
		}
		else
			enemy->cooldown--;
	}
}

void render_enemy(t_game *game, t_enemy *enemy)
{
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
