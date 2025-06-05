/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:17:52 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 16:46:41 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	calculate_shoot(t_game *game)
{
	int		center_ray_index;
	t_ray	*center_ray;

	center_ray_index = DISPLAY_WIDTH / 2;
	center_ray = &game->rays[center_ray_index];
	if (game->current_weapon == PORTALGUN)
		handle_portal_shot(game, center_ray);
	else if (game->current_weapon == RAYGUN)
		handle_raygun_shot(game, center_ray);
}

int	mouse_button(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		handle_left_click(game);
	else if (button == 4 || button == 5)
		handle_scroll_wheel(game, button);
	else if (button == 3 && game->current_weapon == PORTALGUN)
		remove_all_portals(game);
	return (0);
}

void	handle_left_click(t_game *game)
{
	if (game->current_weapon == HANDS)
		return ;
	if (game->current_weapon == RAYGUN)
		shoot_raygun(game);
	else if (game->current_weapon == PORTALGUN)
		shoot_portalgun(game);
	else if (game->current_weapon == HEALGUN)
		use_healgun(game);
}

void	handle_scroll_wheel(t_game *game, int button)
{
	if (button == 4)
		switch_to_next_weapon(game);
	else
		switch_to_previous_weapon(game);
}
