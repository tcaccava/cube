/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:09:31 by abkhefif          #+#    #+#             */
/*   Updated: 2025/06/04 17:11:09 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_color(char *color_str, int *color)
{
	char	*str;
	int		rgb[3];
	int		i;
	int		current_color;

	str = color_str;
	while (*str == ' ')
		str++;
	clean_line_ending(str);
	i = 0;
	current_color = 0;
	rgb[0] = rgb[1] = rgb[2] = 0;
	while (str[i] && current_color < 3)
	{
		if (ft_isdigit(str[i]))
			rgb[current_color] = rgb[current_color] * 10 + (str[i] - '0');
		else if (str[i] == ',')
			current_color++;
		else if (str[i] != ' ')
			return (printf("Error: Invalid RGB format\n"), 0);
		i++;
	}
	if (current_color != 2 || rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (printf("Error: Invalid RGB values (0-255)\n"), 0);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

int	parse_texture(char *path_str, char **texture_path)
{
	char	*path;
	int		fd;
	int		len;

	path = path_str;
	while (*path_str == ' ')
		path_str++;
	clean_line_ending(path);
	len = ft_strlen(path);
	if (len < 4)
		return (printf("Error: Texture path too short: %s\n", path), 0);
	if (path[len - 4] != '.' || path[len - 3] != 'x' || path[len - 2] != 'p'
		|| path[len - 1] != 'm')
		return (printf("Error: Texture must be .xpm format: %s\n", path), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open texture: %s\n", path), 0);
	close(fd);
	*texture_path = ft_strdup(path);
	return (*texture_path != NULL);
}

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

int	finalize_parsing(t_scene_data *scene, t_game *game)
{
	t_texture_paths	paths;

	if (!scene->north_texture || !scene->south_texture || !scene->west_texture
		|| !scene->east_texture)
		return (printf("Error: Missing texture(s)\n"), 0);
	if (scene->map_count == 0)
		return (printf("Error: No map found\n"), 0);
	game->map.matrix[scene->map_count] = NULL;
	game->map.height = scene->map_count;
	game->map.width = calculate_map_width(game);
	game->map.floor_color = scene->floor_color;
	game->map.sky_color = scene->ceiling_color;
	if (!init_mlx_window(game))
		return (printf("Error: MLX init failed\n"), 0);
	init_player(&game->player);
	game->player.game = game;
	if (!set_player_pos(game))
		return (printf("Error: No player position found\n"), 0);
	paths.north = scene->north_texture;
	paths.south = scene->south_texture;
	paths.east = scene->east_texture;
	paths.west = scene->west_texture;
	if (!load_directional_textures(game, &paths))
		return (printf("Error: Failed to load directional textures\n"), 0);
	if (!load_special_textures(game))
		return (printf("Error: Failed to load special textures\n"), 0);
	if (!load_door_textures(game))
		return (printf("Error: Failed to load door textures\n"), 0);
	game->current_weapon = HANDS;
	if (!load_all_weapons(game))
		return (printf("Error: Failed to load weapons\n"), 0);
	if (!load_weapon_pickup_sprites(game))
		return (printf("Error: Failed to load weapon pickups\n"), 0);
	if (!set_weapon_positions(game))
		return (printf("Error: Failed to set weapon positions\n"), 0);
	if (!load_open_door_sprites(game))
		return (printf("Error: Failed to load door sprites\n"), 0);
	if (!set_open_door_positions(game))
		return (printf("Error: Failed to set door positions\n"), 0);
	if (!init_all_enemies(game))
		return (printf("Error: Failed to init enemies\n"), 0);
	init_portals(game);
	init_ui_components(game);
	printf("✅ Game initialized!\n");
	return (1);
}
