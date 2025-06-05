/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sprite_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:27 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/05 20:52:03 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_img	*get_death_sprite(t_enemy *enemy)
{
	return (&enemy->death_morty[enemy->animation.current_frame]);
}

int	setup_death_render(t_game *game, t_enemy *enemy, t_render *renderer)
{
	calculate_enemy_transform(game, enemy, renderer);
	if (renderer->floor_y <= 0.2f)
		return (0);
	calculate_enemy_screen_pos(game, renderer);
	renderer->sprite_size = renderer->sprite_size * 0.6;
	if (renderer->sprite_size < 8)
		renderer->sprite_size = 8;
	return (1);
}

void	apply_death_modifiers(t_enemy *enemy, t_render *renderer)
{
	int	death_y_offset;
	int	death_size_modifier;

	death_y_offset = 0;
	death_size_modifier = 0;
	if (enemy->animation.current_frame == 1)
	{
		death_y_offset = 20;
		death_size_modifier = -10;
	}
	else if (enemy->animation.current_frame == 2)
	{
		death_y_offset = 100;
		death_size_modifier = -20;
	}
	renderer->sprite_size += death_size_modifier;
	if (renderer->sprite_size < 10)
		renderer->sprite_size = 10;
	renderer->draw_end += death_y_offset;
}

int	validate_death_render(t_render *renderer)
{
	if (renderer->x < 0 || renderer->x >= DISPLAY_WIDTH)
		return (0);
	return (1);
}

void	finalize_death_render(t_game *game, t_render *renderer)
{
	setup_enemy_render_params(game, renderer);
}
