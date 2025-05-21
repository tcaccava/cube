#include "cube3d.h"

int	check_borders(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (y == 0 || y == map->height - 1)
		{
			x = 0;
			while (x < map->width)
			{
				if (map->matrix[y][x] != '1')
					return (printf("Error: Invalid Map"));
				x++;
			}
		}
		else if ((map->matrix[y][0] != '1') || (map->matrix[y][map->width
				- 1] != '1'))
			return (printf("Error: Invalid Map"));
		y++;
	}
	return (1);
}

int	check_playable_spaces(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->matrix[y][x] == '0' || map->matrix[y][x] == 'N'
				|| map->matrix[y][x] == 'S' || map->matrix[y][x] == 'E'
				|| map->matrix[y][x] == 'W')
			{
				if (y == 0 || y == map->height - 1 || x == 0 || x == map->width
					- 1)
					return (printf("Error: Invalid Map"));
				if (map->matrix[y - 1][x - 1] == ' ' || map->matrix[y
					- 1][x] == ' ' || map->matrix[y - 1][x + 1] == ' '
					|| map->matrix[y][x - 1] == ' ' || map->matrix[y][x
					+ 1] == ' ' || map->matrix[y + 1][x - 1] == ' '
					|| map->matrix[y + 1][x] == ' ' || map->matrix[y + 1][x
					+ 1] == ' ')
					return (printf("Error: Invalid Map"));
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!check_borders(map))
		return (0);
	if (!check_playable_spaces(map))
		return (0);
	return (1);
}

int	set_player_pos(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.matrix[y][x] == 'N' || game->map.matrix[y][x] == 'E'
				|| game->map.matrix[y][x] == 'S'
				|| game->map.matrix[y][x] == 'W')
			{
				game->player.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				game->player.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				if (game->map.matrix[y][x] == 'N')
					game->player.angle = 3 * M_PI / 2;
				else if (game->map.matrix[y][x] == 'E')
					game->player.angle = 0;
				else if (game->map.matrix[y][x] == 'S')
					game->player.angle = M_PI / 2;
				else if (game->map.matrix[y][x] == 'W')
					game->player.angle = M_PI;
				game->map.matrix[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int set_enemy_pos(t_game *game)
{
    int y;
    int x;
    int idx;

    idx = 0;
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.matrix[y][x] == 'M' && idx < game->num_enemies)
            {
                // Position in grid coordinates (cells)
                // No need to add 0.5 here, that gets added during render
                game->enemies[idx].x = x;
                game->enemies[idx].y = y;
                game->enemies[idx].active = 1;
                game->enemies[idx].state = IDLE;
                game->enemies[idx].health = 100;
                game->enemies[idx].speed = 0.03;
                game->enemies[idx].sees_player = 0;
                game->enemies[idx].angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
                game->enemies[idx].texture = &game->map.enemy_texture;
                
                // Replace the 'M' with '0' in the map to make the space walkable
                game->map.matrix[y][x] = '0';
                idx++;
            }
            x++;
        }
        y++;
    }
    return (idx > 0);
}

int	check_file_cub(char *file_path)
{
	int	i;

	i = ft_strlen(file_path);
	if (i < 4)
		return (0);
	if (file_path[i - 4] == '.' && file_path[i - 3] == 'c' && file_path[i
		- 2] == 'u' && file_path[i - 1] == 'b')
		return (1);
	return (0);
}

int	read_map(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;
	int		line_count;
	int		width;
	int		len;

	line_count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->map.matrix = malloc(sizeof(char *) * (line_count + 1));
	if (!game->map.matrix)
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.matrix);
		return (0);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map.matrix[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->map.matrix[i] = NULL;
	close(fd);
	game->map.height = line_count;
	game->map.width = 0;
	i = 0;
	while (i < game->map.height)
	{
		width = ft_strlen(game->map.matrix[i]);
		if (width > game->map.width)
			game->map.width = width;
		i++;
	}
	return (1);
}
