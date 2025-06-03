/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon_pickups.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:21 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:22 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_weapon_pickup(t_game *game, t_weapon_pickup *weapon)
{
	t_render	renderer;
	int			is_visible;
	double		distance_to_player;

	if (!weapon->active)
		return ;
	if (should_skip_weapon_render(game, weapon))
		return ;
	distance_to_player = calculate_distance_to_weapon(game, weapon);
	if (distance_to_player > 200)
		return ;
	calculate_weapon_transform(game, weapon, &renderer);
	if (renderer.floor_y <= 0.2f)
		return ;
	calculate_weapon_screen_pos(game, &renderer);
	if (renderer.x < 0 || renderer.x >= DISPLAY_WIDTH)
		return ;
	is_visible = check_enemy_occlusion(game, &renderer);
	if (!is_visible)
		return ;
	setup_weapon_pickup_render(game, &renderer);
	draw_weapon_pickup_sprite(game, &weapon->sprite,
		(t_point){renderer.draw_start, renderer.draw_end},
		renderer.sprite_size);
}

int	should_skip_weapon_render(t_game *game, t_weapon_pickup *weapon)
{
	if (weapon->weapon_type == HEALGUN)
		return (setup_healgun_pickup_sprite(game, weapon));
	else if (game->player.has_weapon[weapon->weapon_type])
		return (1);
	return (0);
}

int	setup_healgun_pickup_sprite(t_game *game, t_weapon_pickup *weapon)
{
	if (game->player.has_weapon[HEALGUN])
	{
		if (!load_weapon_pickup_sprite(game, weapon,
				"./texture/w_heal_pickup.xpm"))
			printf("Warning: syringe_pickup.xpm not found\n");
	}
	else
	{
		if (!weapon->sprite.ptr)
			load_weapon_pickup_sprite(game, weapon,
				"./texture/w_healgun_pickup.xpm");
	}
	return (0);
}

void	draw_weapon_pickup_sprite(t_game *game, t_img *sprite, t_point pos,
		int size)
{
	t_weapon_pixel_data	data;
	int					i;

	if (!sprite || !sprite->addr || size <= 0)
		return ;
	data.sprite = sprite;
	data.pos = pos;
	data.size = size;
	i = 0;
	while (i < size)
	{
		data.i = i;
		draw_weapon_pickup_row(game, &data);
		i++;
	}
}

void	draw_weapon_pickup_row(t_game *game, t_weapon_pixel_data *data)
{
	int	j;

	j = 0;
	while (j < data->size)
	{
		data->j = j;
		draw_weapon_pickup_pixel(game, data);
		j++;
	}
}
