/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:16 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:30 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_enemy_sprite(t_game *game, t_img *sprite,
		t_render *renderer, t_enemy *enemy)
{
	int					i;
	int					j;
	t_weapon_pixel_data	data;
	t_point				pos;

	(void)enemy;
	if (!sprite || !sprite->addr || renderer->sprite_size <= 0)
		return ;
	pos.x = renderer->draw_start;
	pos.y = renderer->draw_end;
	i = 0;
	while (i < renderer->sprite_size)
	{
		j = 0;
		while (j < renderer->sprite_size)
		{
			data = (t_weapon_pixel_data){sprite, pos,
				renderer->sprite_size, i, j, enemy->state};
			draw_sprite_pixel_at_pos(game, &data);
			j++;
		}
		i++;
	}
}

void	render_death_animation(t_game *game, t_enemy *enemy)
{
	t_render	renderer;
	t_img		*current_sprite;

	current_sprite = get_death_sprite(enemy);
	if (!setup_death_render(game, enemy, &renderer))
		return ;
	apply_death_modifiers(enemy, &renderer);
	if (!validate_death_render(&renderer))
		return ;
	if (!check_enemy_occlusion(game, &renderer))
		return ;
	finalize_death_render(game, &renderer);
	draw_enemy_sprite(game, current_sprite, &renderer, enemy);
}
