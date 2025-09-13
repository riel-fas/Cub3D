/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:58:58 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 03:21:19 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Skip empty lines and comments
// Skip texture and color lines
static int	find_map_start(t_data *data)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	while (i < data->line_count)
	{
		trimmed_line = ft_strtrim(data->file_lines[i]);
		if (!trimmed_line)
			return (-1);
		
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
		{
			free(trimmed_line);
			i++;
			continue;
		}		
		if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || 
			ft_strncmp(trimmed_line, "SO ", 3) == 0 ||
			ft_strncmp(trimmed_line, "WE ", 3) == 0 || 
			ft_strncmp(trimmed_line, "EA ", 3) == 0 ||
			ft_strncmp(trimmed_line, "F ", 2) == 0 || 
			ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			free(trimmed_line);
			i++;
			continue;
		}
		free(trimmed_line);
		return (i);
	}
	return (-1);
}

static int	count_map_lines(t_data *data, int start)
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

static int	get_map_width(t_data *data, int start)
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

//the function ensures that a given string line is padded with spaces at the end so that its total length matches target_width
static char	*pad_map_line(char *line, int target_width)
{
	char	*padded_line;
	int		original_len;
	int		i;

	original_len = ft_strlen(line);
	padded_line = malloc(target_width + 1);
	if (!padded_line)
		return (NULL);
	i = 0;
	while (i < original_len)
	{
		padded_line[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded_line[i] = ' ';
		i++;
	}
	padded_line[target_width] = '\0';
	return (padded_line);
}

int	parse_map(t_data *data)
{
	int		map_start;
	int		map_line_count;
	int		i;
	int		map_index;
	char	*trimmed_line;
	char	*padded_line;

	map_start = find_map_start(data);
	if (map_start == -1)
	{
		printf("❌ No map found in file\n");
		return (FALSE);
	}	
	printf("🗺️  Map starts at line %d\n", map_start + 1);
	map_line_count = count_map_lines(data, map_start);
	if (map_line_count <= 0)
	{
		printf("❌ Invalid map\n");
		return (FALSE);
	}
	data->map_width = get_map_width(data, map_start);
	if (data->map_width <= 0)
	{
		printf("❌ Invalid map width\n");
		return (FALSE);
	}
	data->map_height = map_line_count;
	printf("📏 Map dimensions: %d x %d\n", data->map_width, data->map_height);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (FALSE);
	i = map_start;
	map_index = 0;
	while (i < data->line_count && map_index < data->map_height)
	{
		trimmed_line = ft_strtrim(data->file_lines[i]);
		if (!trimmed_line)
		{
			printf("❌ Memory allocation error\n");
			return (FALSE);
		}
		if (trimmed_line[0] != '\0')
		{
			padded_line = pad_map_line(trimmed_line, data->map_width);
			if (!padded_line)
			{
				free(trimmed_line);
				return (FALSE);
			}	
			data->map[map_index] = padded_line;
			printf("🗺️  Line %d: %s\n", map_index, data->map[map_index]);
			map_index++;
		}
		free(trimmed_line);
		i++;
	}
	data->map[map_index] = NULL;
	printf("✅ Map parsing completed\n");
	return (TRUE);
}
