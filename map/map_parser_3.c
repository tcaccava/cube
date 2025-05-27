/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:52:49 by tcaccava          #+#    #+#             */
/*   Updated: 2025/05/27 21:30:10 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	read_maps(char *file_path, t_game *game)
{
	int	line_count;

	line_count = count_lines(file_path);
	if (line_count <= 0)
		return (0);
	if (!allocate_matrix(game, line_count))
		return (0);
	if (!fill_matrix(file_path, game))
		return (0);
	set_map_dimensions(game, line_count);
	return (1);
}

int	count_lines(char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	allocate_matrix(t_game *game, int line_count)
{
	game->map.matrix = malloc(sizeof(char *) * (line_count + 1));
	return (game->map.matrix != NULL);
}

int	fill_matrix(char *file_path, t_game *game)
{
	int		fd;
	int		i;
	char	*line;
	int		len;

	i = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map.matrix[i++] = line;
		line = get_next_line(fd);
	}
	game->map.matrix[i] = NULL;
	close(fd);
	return (1);
}

void	set_map_dimensions(t_game *game, int height)
{
	int	i;
	int	width;

	i = 0;
	game->map.height = height;
	game->map.width = 0;
	while (i < height)
	{
		width = ft_strlen(game->map.matrix[i]);
		if (width > game->map.width)
			game->map.width = width;
		i++;
	}
}
