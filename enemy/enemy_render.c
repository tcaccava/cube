/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:23 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:24 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	calculate_sprite_bounds(t_render *render, int *start, int *end)
{
	int	sprite_left_edge;

	sprite_left_edge = render->x - render->sprite_size / 2;
	if (sprite_left_edge < 0)
		*start = 0;
	else
		*start = sprite_left_edge;
	*end = sprite_left_edge + render->sprite_size - 1;
	if (*end >= DISPLAY_WIDTH)
		*end = DISPLAY_WIDTH - 1;
	return (0);
}

static void	handle_dead_enemy(t_game *game, t_enemy *enemy)
{
	if (enemy->death_timer > 0)
		enemy->death_timer--;
	else
		enemy->active = 0;
	update_death_animation(enemy);
	render_death_animation(game, enemy);
}

static t_img	*get_current_sprite(t_enemy *enemy)
{
	if (enemy->state == SHOOT)
		return (&enemy->shoot_morty[enemy->animation.current_frame]);
	else
		return (&enemy->walk_morty[enemy->animation.current_frame]);
}

void	render_enemy(t_game *game, t_enemy *enemy)
{
	t_render	renderer;
	t_img		*current_sprite;
	int			is_visible;

	if (enemy->state == DEAD)
	{
		handle_dead_enemy(game, enemy);
		return ;
	}
	update_enemy_animation(enemy);
	current_sprite = get_current_sprite(enemy);
	calculate_enemy_transform(game, enemy, &renderer);
	if (renderer.floor_y <= 0.2f)
		return ;
	calculate_enemy_screen_pos(game, &renderer);
	if (renderer.x < 0 || renderer.x >= DISPLAY_WIDTH)
		return ;
	is_visible = check_enemy_occlusion(game, &renderer);
	if (!is_visible)
		return ;
	setup_enemy_render_params(game, &renderer);
	draw_enemy_sprite(game, current_sprite, &renderer, enemy);
}
