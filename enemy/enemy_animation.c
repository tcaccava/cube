/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:03:40 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 20:03:44 by tcaccava         ###   ########.fr       */
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
	}
}

static void	advance_animation(t_enemy *enemy)
{
	enemy->animation.frame_counter++;
	if (enemy->animation.frame_counter >= ANIMATION_SPEED)
	{
		enemy->animation.current_frame = (enemy->animation.current_frame + 1)
			% 2;
		enemy->animation.frame_counter = 0;
	}
}

void	update_enemy_animation(t_enemy *enemy)
{
	if (!enemy->active)
		return ;
	if (enemy->state == DEAD)
		return (update_death_animation(enemy), (void)0);
	if (enemy->state == SEARCH || enemy->state == IDLE || enemy->state == SHOOT)
		advance_animation(enemy);
}
