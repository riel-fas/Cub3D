/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:51:14 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 22:26:27 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_or_comment(char *line)
{
	return (line[0] == '\0' || line[0] == '#');
}

static int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || 
			ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || 
			ft_strncmp(line, "EA ", 3) == 0);
}

static int	is_color_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || 
			ft_strncmp(line, "C ", 2) == 0);
}

static int	process_single_line(t_data *data, char *trimmed_line)
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

static int	validate_parsing_completeness(t_data *data)
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

static char	*get_trimmed_line(char **file_lines, int index)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(file_lines[index]);
	return (trimmed_line);
}

static int	handle_line_processing_result(int result, char *trimmed_line)
{
	if (result == FALSE)
	{
		free(trimmed_line);
		return (FALSE);
	}
	if (result == -1)
	{
		free(trimmed_line);
		return (-1);
	}
	free(trimmed_line);
	return (TRUE);
}

static int	process_single_line_with_cleanup(t_data *data, char *trimmed_line)
{
	int	result;

	if (is_empty_or_comment(trimmed_line))
	{
		free(trimmed_line);
		return (2);
	}
	result = process_single_line(data, trimmed_line);
	return (handle_line_processing_result(result, trimmed_line));
}

static int	iterate_through_lines(t_data *data)
{
	int		i;
	char	*trimmed_line;
	int		result;

	i = 0;
	while (i < data->line_count)
	{
		trimmed_line = get_trimmed_line(data->file_lines, i);
		if (!trimmed_line)
			return (FALSE);
		result = process_single_line_with_cleanup(data, trimmed_line);
		if (result == FALSE)
			return (FALSE);
		if (result == -1)
			break;
		if (result == 2)
		{
			i++;
			continue;
		}
		i++;
	}
	return (TRUE);
}

static int	process_lines_until_map(t_data *data)
{
	return (iterate_through_lines(data));
}

int	parse_textures_and_colors(t_data *data)
{
	if (!process_lines_until_map(data))
		return (FALSE);
	return (validate_parsing_completeness(data));
}
