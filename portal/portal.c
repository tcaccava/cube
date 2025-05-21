#include "./cube3d.h"

void remove_all_portals(t_game *game)
{
	int y;
	int x;
	int i;
	
	i = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.matrix[y][x] == 'P')
				game->map.matrix[y][x] = '1';
			x++;
		}
		y++;
	}
	game->portal_count = 0;
	while (i < DISPLAY_WIDTH)
	{
		double ray_offset = game->player.fov * ((double)i / DISPLAY_WIDTH - 0.5);
		double radiant_angle = normalize_angle(game->player.angle + ray_offset);
		game->rays[i].radiant_angle = radiant_angle;
		game->rays[i].player_angle = game->player.angle;
		game->rays[i].distance = ray_casting(game, radiant_angle, i);
		i++;
	}
}
