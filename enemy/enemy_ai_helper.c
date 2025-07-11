/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:05 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/09 02:51:31 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	handle_shoot_cooldown(t_enemy *e, t_player *p)
{
	if (e->cooldown <= 0)
	{
		p->health -= 10;
		e->cooldown = 180;
	}
	else
		e->cooldown--;
}

void	handle_melee_cooldown(t_enemy *e, t_player *p)
{
	if (e->cooldown <= 0)
	{
		p->health -= 15;
		e->cooldown = 90;
	}
	else
		e->cooldown--;
}
