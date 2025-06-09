/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:09:31 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/09 18:43:41 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_cub_file(char *filename, t_game *game)
{
	int				fd;
	char			*line;
	t_scene_data	scene;

	ft_memset(&scene, 0, sizeof(t_scene_data));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open %s\n", filename), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(line, &scene, game))
		{
			printf("Error in line: %s", line);
			free(line);
			close(fd);
			cleanup_scene(&scene);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (finalize_parsing(&scene, game));
}

int	process_line(char *line, t_scene_data *scene, t_game *game)
{
	char	*line_content;

	line_content = line;
	while (*line_content == ' ' || *line_content == '\t')
		line_content++;
	if (*line_content == '\0' || *line_content == '\n')
		return (1);
	if (scene->map_started)
		return (add_map_line(line_content, game, scene));
	if (ft_strncmp(line_content, "NO ", 3) == 0)
		return (parse_texture(line_content + 3, &scene->north_texture));
	if (ft_strncmp(line_content, "SO ", 3) == 0)
		return (parse_texture(line_content + 3, &scene->south_texture));
	if (ft_strncmp(line_content, "WE ", 3) == 0)
		return (parse_texture(line_content + 3, &scene->west_texture));
	if (ft_strncmp(line_content, "EA ", 3) == 0)
		return (parse_texture(line_content + 3, &scene->east_texture));
	if (ft_strncmp(line_content, "F ", 2) == 0)
		return (parse_color(line_content + 2, &scene->floor_color));
	if (ft_strncmp(line_content, "C ", 2) == 0)
		return (parse_color(line_content + 2, &scene->ceiling_color));
	scene->map_started = 1;
	return (add_map_line(line_content, game, scene));
}

int	add_map_line(char *line, t_game *game, t_scene_data *scene)
{
	clean_line_ending(line);
	if (!game->map.matrix)
	{
		game->map.matrix = malloc(sizeof(char *) * 1000);
		if (!game->map.matrix)
			return (printf("Error: Memory allocation failed\n"), 0);
	}
	game->map.matrix[scene->map_count] = ft_strdup(line);
	if (!game->map.matrix[scene->map_count])
		return (printf("Error: Memory allocation failed\n"), 0);
	scene->map_count++;
	return (1);
}

int	validate_textures(t_scene_data *scene)
{
	if (!scene->north_texture || !scene->south_texture || !scene->west_texture
		|| !scene->east_texture)
		return (printf("Error: Missing texture(s)\n"), 0);
	return (1);
}
