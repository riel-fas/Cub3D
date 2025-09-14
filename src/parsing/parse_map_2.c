/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:45:39 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 01:44:45 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_config_line(char *trimmed_line)
{
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0
		|| ft_strncmp(trimmed_line, "SO ", 3) == 0
		|| ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0
		|| ft_strncmp(trimmed_line, "F ", 2) == 0
		|| ft_strncmp(trimmed_line, "C ", 2) == 0)
		return (TRUE);
	return (FALSE);
}

int	should_skip_line(char *trimmed_line)
{
	if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
		return (TRUE);
	if (is_config_line(trimmed_line))
		return (TRUE);
	return (FALSE);
}

// Skip empty lines and comments
// Skip texture and color lines
int	find_map_start(t_data *data)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (i < data->line_count)
	{
		trimmed_line = ft_strtrim(data->file_lines[i]);
		if (!trimmed_line)
			return (-1);
		if (should_skip_line(trimmed_line))
		{
			free(trimmed_line);
			i++;
			continue ;
		}
		free(trimmed_line);
		return (i);
	}
	return (-1);
}

int	count_map_lines(t_data *data, int start)
{
	int		count;
	int		i;
	char	*trimmed_line;

	count = 0;
	i = start;
	while (i < data->line_count)
	{
		trimmed_line = ft_strtrim(data->file_lines[i]);
		if (!trimmed_line)
			return (-1);
		if (trimmed_line[0] != '\0')
			count++;
		free(trimmed_line);
		i++;
	}
	return (count);
}

int	get_map_width(t_data *data, int start)
{
	int		max_width;
	int		current_width;
	int		i;
	char	*trimmed_line;

	max_width = 0;
	i = start;
	while (i < data->line_count)
	{
		trimmed_line = ft_strtrim(data->file_lines[i]);
		if (!trimmed_line)
			return (-1);
		if (trimmed_line[0] != '\0')
		{
			current_width = ft_strlen(trimmed_line);
			if (current_width > max_width)
				max_width = current_width;
		}
		free(trimmed_line);
		i++;
	}
	return (max_width);
}
