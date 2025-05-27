/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:03:05 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 19:54:07 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	should_skip_pixel(t_enemy *enemy, int red, int green, int blue)
{
	int	tolerance;

	if (enemy->state == DEAD)
	{
		if (red > 180 && blue > 180 && green < 100)
			return (1);
	}
	else
	{
		tolerance = 2;
		if (abs(red - 255) <= tolerance && abs(green - 0) <= tolerance
			&& abs(blue - 0) <= tolerance)
			return (1);
	}
	return (0);
}

static unsigned int	extract_sprite_color(t_img *sprite, int i, int j, int size)
{
	int		src_x;
	int		src_y;
	char	*src;

	src_x = i * sprite->width / size;
	src_y = j * sprite->height / size;
	if (src_x < 0)
		src_x = 0;
	else if (src_x >= sprite->width)
		src_x = sprite->width - 1;
	if (src_y < 0)
		src_y = 0;
	else if (src_y >= sprite->height)
		src_y = sprite->height - 1;
	src = sprite->addr + src_y * sprite->line_length + src_x
		* (sprite->bits_per_pixel / 8);
	return (*(unsigned int *)src);
}

static int	should_draw_pixel(t_sprite_info *info, int i, int j,
		unsigned int *out_color)
{
	unsigned int	color;

	color = extract_sprite_color(info->sprite, i, j, info->size);
	if (!should_skip_pixel(info->enemy, (color >> 16) & 0xFF,
			(color >> 8) & 0xFF, color & 0xFF))
	{
		*out_color = color;
		return (1);
	}
	return (0);
}

void	draw_sprite_pixel(t_sprite_info *info, int i, int j)
{
	int				x;
	int				y;
	char			*dst;
	unsigned int	color;

	if (!should_draw_pixel(info, i, j, &color))
		return ;
	x = info->pos.x + i;
	y = info->pos.y + j;
	if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT)
		return ;
	dst = info->game->screen.addr + y * info->game->screen.line_length + x
		* (info->game->screen.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	draw_enemy_sprite(t_sprite_info *info)
{
	int	i;
	int	j;

	if (!info->sprite || !info->sprite->addr || info->size <= 0)
		return ;
	i = 0;
	while (i < info->size)
	{
		j = 0;
		while (j < info->size)
		{
			draw_sprite_pixel(info, i, j);
			j++;
		}
		i++;
	}
}
