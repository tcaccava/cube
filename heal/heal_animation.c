/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heal_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:21:06 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:21:07 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	update_healgun_animation(t_game *game)
{
	if (!game->player.healgun_animating)
		return ;
	game->player.healgun_anim_timer--;
	if (game->player.healgun_anim_timer <= 0)
		advance_heal_frame(game);
}

void	advance_heal_frame(t_game *game)
{
	int	frame_durations[5];

	set_frame_durations(frame_durations);
	game->player.healgun_anim_frame++;
	if (game->player.healgun_anim_frame >= 5)
		finish_heal_animation(game);
	else
		set_next_frame_timer(game, frame_durations);
}

void	set_frame_durations(int frame_durations[5])
{
	frame_durations[0] = 4;
	frame_durations[1] = 6;
	frame_durations[2] = 10;
	frame_durations[3] = 6;
	frame_durations[4] = 4;
}

void	finish_heal_animation(t_game *game)
{
	game->player.healgun_animating = 0;
	game->player.healgun_anim_frame = 0;
	printf("✅ Animation Heal Gun terminée !\n");
}

void	set_next_frame_timer(t_game *game, int frame_durations[5])
{
	game->player.healgun_anim_timer = frame_durations
	[game->player.healgun_anim_frame];
	printf("💉 Frame healgun: %d\n", game->player.healgun_anim_frame);
}
