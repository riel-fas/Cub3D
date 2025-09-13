/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:33:49 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 22:40:57 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_or_comment(char *line)
{
	return (line[0] == '\0' || line[0] == '#');
}

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
        || ft_strncmp(line, "SO ", 3) == 0
        || ft_strncmp(line, "WE ", 3) == 0
        || ft_strncmp(line, "EA ", 3) == 0);
}

int	is_color_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0
        || ft_strncmp(line, "C ", 2) == 0);
}

int	process_single_line(t_data *data, char *trimmed_line)
{
	if (is_texture_line(trimmed_line))
	{
		if (!parse_texture_line(data, trimmed_line))
			return (FALSE);
	}
	else if (is_color_line(trimmed_line))
	{
		if (!parse_color_line(data, trimmed_line))
			return (FALSE);
	}
	else if (trimmed_line[0] != '\0')
		return (-1);
	return (TRUE);
}

int	validate_parsing_completeness(t_data *data)
{
	int total_textures;
	int total_colors;

	total_textures = data->textures_parsed[0] + data->textures_parsed[1] + 
				 data->textures_parsed[2] + data->textures_parsed[3];
	total_colors = data->colors_parsed[0] + data->colors_parsed[1];
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
