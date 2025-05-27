/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sprite_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:27:46 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 19:41:59 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	get_death_animation_params(t_enemy *enemy, int *offset,
		int *size_mod)
{
	if (enemy->animation.current_frame == 0)
	{
		*offset = 0;
		*size_mod = 0;
	}
	else if (enemy->animation.current_frame == 1)
	{
		*offset = 20;
		*size_mod = -10;
	}
	else
	{
		*offset = 100;
		*size_mod = -20;
	}
}

void	render_enemy_sprite(t_game *game, t_img *sprite,
			t_render *renderer, t_enemy *enemy)
{
	t_sprite_info	info;

	info.game = game;
	info.sprite = sprite;
	info.pos = (t_point){renderer->draw_start, renderer->draw_end};
	info.size = renderer->sprite_size;
	info.enemy = enemy;
	draw_enemy_sprite(&info);
}

void	render_death_animation(t_game *game, t_enemy *enemy)
{
	t_render		renderer;
	t_img			*current_sprite;
	int				death_y_offset;
	int				death_size_modifier;
	int				is_visible;

	get_death_animation_params(enemy, &death_y_offset, &death_size_modifier);
	current_sprite = &enemy->death_morty[enemy->animation.current_frame];
	calculate_enemy_transform(game, enemy, &renderer);
	if (renderer.floor_y <= 0.2f)
		return ;
	calculate_enemy_screen_pos(game, &renderer);
	renderer.sprite_size += death_size_modifier;
	if (renderer.sprite_size < 10)
		renderer.sprite_size = 10;
	if (renderer.x < 0 || renderer.x >= DISPLAY_WIDTH)
		return ;
	is_visible = check_enemy_occlusion(game, &renderer);
	if (!is_visible)
		return ;
	setup_enemy_render_params(game, &renderer);
	renderer.draw_end += death_y_offset;
	render_enemy_sprite(game, current_sprite, &renderer, enemy);
}
