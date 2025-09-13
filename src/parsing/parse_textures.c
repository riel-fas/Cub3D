/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:51:14 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 20:51:17 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_type(char *line)
{
	if (!line)
		return (-1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA);
	return (-1);
}

static int	validate_texture_extension(char *path)
{
	int	len;

	if (!path)
		return (FALSE);
	len = ft_strlen(path);
	if (len < 4)
		return (FALSE);
	return (ft_strncmp(path + len - 4, ".png", 4) == 0 || 
			ft_strncmp(path + len - 4, ".PNG", 4) == 0);
}

// skip texture identifier and spaces
// Validate .xpm extension
// Check if file exists
// Check if texture already set
static int	parse_texture_line(t_data *data, char *line)
{
	int		type;
	char	*path;
	int		fd;
	int		i;

	type = get_texture_type(line);
	if (type == -1)
		return (FALSE);
	
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
	{
		printf("❌ No texture path found for %s\n", 
			   (type == NO) ? "NO" : (type == SO) ? "SO" : 
			   (type == WE) ? "WE" : "EA");
		return (FALSE);
	}
	path = ft_strtrim(&line[i]);
	if (!path)
		return (FALSE);	
	if (!validate_texture_extension(path))
	{
		printf("❌ Texture file must have .xpm extension: %s\n", path);
		free(path);
		return (FALSE);
	}

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Cannot open texture file: %s\n", path);
		free(path);
		return (FALSE);
	}
	close(fd);
	if (data->textures_parsed[type])
	{
		printf("❌ Duplicate texture definition: %s\n", 
			   (type == NO) ? "NO" : (type == SO) ? "SO" : 
			   (type == WE) ? "WE" : "EA");
		free(path);
		return (FALSE);
	}	
	data->texture_paths[type] = path;
	data->textures_parsed[type] = 1;
	printf("✅ Texture %s: %s\n", 
		   (type == NO) ? "NO" : (type == SO) ? "SO" : 
		   (type == WE) ? "WE" : "EA", path);
	
	return (TRUE);
}

	// Count elements
	// Parse and validate RGB values
static int	parse_rgb_values(char *rgb_str, t_color *color)
{
	char	**rgb_split;
	int		values[3];
	int		i;

	rgb_split = ft_split(rgb_str, ',');
	if (!rgb_split)
		return (FALSE);
	
	i = 0;
	while (rgb_split[i])
		i++;
	
	if (i != 3)
	{
		free_split(rgb_split);
		return (FALSE);
	}
	for (i = 0; i < 3; i++)
	{
		rgb_split[i] = ft_strtrim(rgb_split[i]);
		if (!rgb_split[i])
		{
			free_split(rgb_split);
			return (FALSE);
		}
		values[i] = ft_atoi(rgb_split[i]);
		if (values[i] < 0 || values[i] > 255)
		{
			free_split(rgb_split);
			return (FALSE);
		}
	}
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	free_split(rgb_split);
	return (TRUE);
}

	// Check if color already set
	// Skip spaces
static int	parse_color_line(t_data *data, char *line)
{
	int		i;
	t_color	*target_color;
	char	*type_name;
	int		*color_flag;

	if (ft_strncmp(line, "F ", 2) == 0)
	{
		target_color = &data->floor_color;
		type_name = "Floor";
		color_flag = &data->colors_parsed[0];
		i = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		target_color = &data->ceiling_color;
		type_name = "Ceiling";
		color_flag = &data->colors_parsed[1];
		i = 1;
	}
	else
		return (FALSE);





	if (*color_flag)
	{
		printf("❌ Duplicate color definition: %s\n", type_name);
		return (FALSE);
	}
	i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
	{
		printf("❌ No color values found for %s\n", type_name);
		return (FALSE);
	}
	if (!parse_rgb_values(&line[i], target_color))
	{
		printf("❌ Invalid RGB values for %s\n", type_name);
		return (FALSE);
	}
	*color_flag = 1;
	printf("✅ %s color: RGB(%d, %d, %d)\n", 
		   type_name, target_color->r, target_color->g, target_color->b);
	
	return (TRUE);
}

// Skip empty lines and comments
// Check if it's a texture line
// Check if it's a color line
// If it's not empty and not texture/color, we've reached the map
// Verify all textures and colors are parsed
int	parse_textures_and_colors(t_data *data)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (i < data->line_count)
	{
		trimmed_line = ft_strtrim(data->file_lines[i]);
		if (!trimmed_line)
			return (FALSE);
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
		{
			free(trimmed_line);
			i++;
			continue;
		}
		if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || 
			ft_strncmp(trimmed_line, "SO ", 3) == 0 ||
			ft_strncmp(trimmed_line, "WE ", 3) == 0 || 
			ft_strncmp(trimmed_line, "EA ", 3) == 0)
		{
			if (!parse_texture_line(data, trimmed_line))
			{
				free(trimmed_line);
				return (FALSE);
			}
		}
		else if (ft_strncmp(trimmed_line, "F ", 2) == 0 || 
				 ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			if (!parse_color_line(data, trimmed_line))
			{
				free(trimmed_line);
				return (FALSE);
			}
		}
		else if (trimmed_line[0] != '\0')
		{
			free(trimmed_line);
			break;
		}
		free(trimmed_line);
		i++;
	}
	int total_textures = data->textures_parsed[0] + data->textures_parsed[1] + 
						 data->textures_parsed[2] + data->textures_parsed[3];
	int total_colors = data->colors_parsed[0] + data->colors_parsed[1];
	if (total_textures != 4)
	{
		printf("❌ Missing textures. Found %d/4\n", total_textures);
		return (FALSE);
	}
	if (total_colors != 2)
	{
		printf("❌ Missing colors. Found %d/2\n", total_colors);
		return (FALSE);
	}
	return (TRUE);
}
