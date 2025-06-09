/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:34:29 by tcaccava          #+#    #+#             */
/*   Updated: 2025/06/09 18:34:40 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	validate_rgb_format(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] == ',')
				commas++;
			else
				return (printf("Error: Invalid character '%c' in RGB format\n",
						str[i]), 0);
		}
		i++;
	}
	if (commas != 2)
		return (printf("Error: RGB must have exactly 2 commas\n"), 0);
	return (1);
}

static int	parse_rgb_component(char *str, int *i)
{
	long	value;

	if (!ft_isdigit(str[*i]))
		return (printf("Error: RGB must start with digit\n"), -1);
	value = 0;
	while (ft_isdigit(str[*i]))
	{
		value = value * 10 + (str[*i] - '0');
		if (value > 2147483647)
			return (printf("Error: RGB value too large (exceeds int max)\n"),
				-1);
		(*i)++;
	}
	if (value > 255)
		return (printf("Error: RGB value %ld exceeds 255\n", value), -1);
	return ((int)value);
}

static int	validate_separator(char *str, int i, int comp)
{
	if (comp < 2)
	{
		if (str[i] != ',')
			return (printf("Error: Expected ',' after RGB value %d\n", comp
					+ 1), 0);
		return (1);
	}
	if (str[i] != '\0')
		return (printf("Error: Expected end of line after 3rd RGB value\n"), 0);
	return (1);
}

int	parse_color(char *color_str, int *color)
{
	int	rgb[3];
	int	i;
	int	comp;
	int	value;

	clean_line_ending(color_str);
	if (!validate_rgb_format(color_str))
		return (0);
	i = 0;
	comp = 0;
	while (comp < 3)
	{
		value = parse_rgb_component(color_str, &i);
		if (value == -1)
			return (0);
		rgb[comp] = value;
		if (!validate_separator(color_str, i, comp))
			return (0);
		if (comp < 2)
			i++;
		comp++;
	}
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

int	parse_texture(char *path_str, char **texture_path)
{
	char	*path;
	int		fd;
	int		len;

	while (*path_str == ' ')
		path_str++;
	path = path_str;
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
	if (*texture_path)
	{
		free(*texture_path);
		*texture_path = NULL;
	}
	*texture_path = ft_strdup(path);
	return (*texture_path != NULL);
}
