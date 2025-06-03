/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:51 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:52 by abkhefif         ###   ########.fr       */
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
