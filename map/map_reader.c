/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:51 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/12 13:16:21 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	read_map_lines(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.matrix);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		clean_line_ending(line);
		game->map.matrix[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->map.matrix[i] = NULL;
	close(fd);
	return (1);
}

int	set_map_dimensions(t_game *game, int line_count)
{
	game->map.height = line_count;
	game->map.width = calculate_map_width(game);
	return (1);
}

int	read_map(char *file_path, t_game *game)
{
	int	line_count;

	line_count = count_file_lines(file_path);
	if (line_count <= 0)
		return (0);
	if (!allocate_map_matrix(game, line_count))
		return (0);
	if (!read_map_lines(file_path, game))
		return (0);
	set_map_dimensions(game, line_count);
	return (1);
}

int	is_valid_playable_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_borders(t_map *map)
{
	int	x;
	int	y;
	int	row_length;

	y = -1;
	while (++y < map->height)
	{
		row_length = ft_strlen(map->matrix[y]);
		if (y == 0 || y == map->height - 1)
		{
			x = -1;
			while (++x < row_length)
				if (map->matrix[y][x] != '1' && map->matrix[y][x] != ' ')
					return (printf("Error: Invalid Map borders"), 0);
		}
		else if ((row_length > 0 && map->matrix[y][0] != '1'
			&& map->matrix[y][0] != ' ') || (row_length > 1
				&& map->matrix[y][row_length - 1] != '1'
				&& map->matrix[y][row_length - 1] != ' '))
			return (printf("Error: Invalid Map borders"), 0);
	}
	return (1);
}
