/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:55:36 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 19:47:15 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	render_enemy_core(t_game *game, t_enemy *enemy, t_render *renderer,
		t_img **current_sprite)
{
	t_sprite_info	info;

	update_enemy_animation(enemy);
	if (enemy->state == SHOOT)
		*current_sprite = &enemy->shoot_morty[enemy->animation.current_frame];
	else
		*current_sprite = &enemy->walk_morty[enemy->animation.current_frame];
	calculate_enemy_transform(game, enemy, renderer);
	if (renderer->floor_y <= 0.2f)
		return ;
	calculate_enemy_screen_pos(game, renderer);
	if (renderer->x < 0 || renderer->x >= DISPLAY_WIDTH)
		return ;
	if (!check_enemy_occlusion(game, renderer))
		return ;
	setup_enemy_render_params(game, renderer);
	info.game = game;
	info.sprite = *current_sprite;
	info.pos = (t_point){renderer->draw_start, renderer->draw_end};
	info.size = renderer->sprite_size;
	info.enemy = enemy;
	draw_enemy_sprite(&info);
}

void	render_enemy(t_game *game, t_enemy *enemy)
{
	t_render	renderer;
	t_img		*current_sprite;

	if (enemy->state == DEAD)
	{
		if (enemy->death_timer > 0)
			enemy->death_timer--;
		else
		{
			enemy->active = 0;
			return ;
		}
		update_death_animation(enemy);
		render_death_animation(game, enemy);
		return ;
	}
	render_enemy_core(game, enemy, &renderer, &current_sprite);
}
