/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		
		// Skip empty lines and comments
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
		{
			free(trimmed_line);
			i++;
			continue;
		}
		
		// Skip texture and color lines
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
		
		// This should be the start of the map
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
		
		// Count non-empty lines
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

static char	*pad_map_line(char *line, int target_width)
{
	char	*padded_line;
	int		original_len;
	int		i;

	original_len = ft_strlen(line);
	padded_line = malloc(target_width + 1);
	if (!padded_line)
		return (NULL);
	
	// Copy original line
	i = 0;
	while (i < original_len)
	{
		padded_line[i] = line[i];
		i++;
	}
	
	// Pad with spaces
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

	// Find where the map starts
	map_start = find_map_start(data);
	if (map_start == -1)
	{
		printf("❌ No map found in file\n");
		return (FALSE);
	}
	
	printf("🗺️  Map starts at line %d\n", map_start + 1);
	
	// Count map lines and get width
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
	
	// Allocate map array
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (FALSE);
	
	// Parse map lines
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
			// Pad line to consistent width
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
