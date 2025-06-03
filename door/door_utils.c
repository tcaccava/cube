/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:58 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:59 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_door_column(t_game *game, int column_x, t_render *renderer)
{
	int		cy;
	double	h;
	int		texture_y;

	cy = (DISPLAY_HEIGHT / 2) + game->pitch;
	h = renderer->wall_height;
	renderer->y = renderer->draw_start;
	while (renderer->y <= renderer->draw_end)
	{
		if (renderer->y >= 0 && renderer->y < DISPLAY_HEIGHT)
		{
			texture_y = calculate_texture_y(renderer, cy, h);
			render_door_pixel(game, column_x, renderer, texture_y);
		}
		renderer->y++;
	}
}

int	calculate_texture_y(t_render *renderer, int cy, double h)
{
	float	rel;
	int		texture_y;

	rel = ((renderer->y - cy) / h) + 0.5f;
	texture_y = (int)(rel * TILE_SIZE);
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= TILE_SIZE)
		texture_y = TILE_SIZE - 1;
	return (texture_y);
}

void	render_door_pixel(t_game *game, int column_x, t_render *renderer,
		int texture_y)
{
	renderer->tex_addr = game->map.door_texture.addr
		+ (texture_y * game->map.door_texture.line_length
			+ renderer->tex_x * (game->map.door_texture.bits_per_pixel / 8));
	renderer->color = *(unsigned int *)renderer->tex_addr;
	renderer->screen_pixel = game->screen.addr
		+ (renderer->y * game->screen.line_length
			+ column_x * (game->screen.bits_per_pixel / 8));
	*(unsigned int *)renderer->screen_pixel = renderer->color;
}

void	setup_door_at_position(t_game *game, int x, int y, int *door_index)
{
	game->open_doors[*door_index].x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->open_doors[*door_index].y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	game->open_doors[*door_index].active = 1;
	printf("🚪 Porte ouverte initialisée à [%d,%d]\n", x, y);
	(*door_index)++;
}

int	load_single_door_sprite(t_game *game, int index)
{
	int	width;
	int	height;

	game->open_doors[index].sprite.ptr = mlx_xpm_file_to_image(game->mlx,
			"./texture/door_open.xpm", &width, &height);
	if (!game->open_doors[index].sprite.ptr)
		return (0);
	setup_texture_data(&game->open_doors[index].sprite, width, height);
	return (1);
}
