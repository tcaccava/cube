/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:15 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:16 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	update_death_animation(t_enemy *enemy)
{
	int	frame_duration;

	if (enemy->state != DEAD)
		return ;
	enemy->animation.frame_counter++;
	if (enemy->animation.current_frame == 0)
		frame_duration = 10;
	else if (enemy->animation.current_frame == 1)
		frame_duration = 4;
	else
		frame_duration = 300;
	if (enemy->animation.frame_counter >= frame_duration)
	{
		enemy->animation.current_frame++;
		if (enemy->animation.current_frame >= 3)
			enemy->animation.current_frame = 2;
		enemy->animation.frame_counter = 0;
		printf("Death progression: frame %d\n", enemy->animation.current_frame);
	}
}

static void	animate_standard_frames(t_enemy *enemy)
{
	enemy->animation.frame_counter++;
	if (enemy->animation.frame_counter >= ANIMATION_SPEED)
	{
		enemy->animation.current_frame = (
				enemy->animation.current_frame + 1) % 2;
		enemy->animation.frame_counter = 0;
	}
}

void	update_enemy_animation(t_enemy *enemy)
{
	if (!enemy->active)
		return ;
	if (enemy->state == DEAD)
		update_death_animation(enemy);
	else if (enemy->state != MELEE)
		animate_standard_frames(enemy);
}
