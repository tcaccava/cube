/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:20:49 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:50 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_file_cub(char *file_path)
{
	int	i;

	i = ft_strlen(file_path);
	if (i < 4)
		return (0);
	if (file_path[i - 4] == '.' && file_path[i - 3] == 'c'
		&& file_path[i - 2] == 'u' && file_path[i - 1] == 'b')
		return (1);
	return (0);
}

int	count_file_lines(char *file_path)
{
	int		fd;
	char	*line;
	int		line_count;

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
	return (line_count);
}

int	calculate_map_width(t_game *game)
{
	int	width;
	int	i;
	int	current_width;

	width = 0;
	i = 0;
	while (i < game->map.height)
	{
		current_width = ft_strlen(game->map.matrix[i]);
		if (current_width > width)
			width = current_width;
		i++;
	}
	return (width);
}

int	allocate_map_matrix(t_game *game, int line_count)
{
	game->map.matrix = malloc(sizeof(char *) * (line_count + 1));
	if (!game->map.matrix)
		return (0);
	return (1);
}

void	clean_line_ending(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
