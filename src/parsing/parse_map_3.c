/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:48:21 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 20:49:28 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//the function ensures that a given string line is padded 
//with spaces at the end so that its total length matches target_width
char	*pad_map_line(char *line, int target_width)
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

int	initialize_map_data(t_data *data, int *map_start)
{
	int	map_line_count;

	*map_start = find_map_start(data);
	if (*map_start == -1)
	{
		printf("❌ No map found in file\n");
		return (FALSE);
	}
	printf("🗺️  Map starts at line %d\n", *map_start + 1);
	map_line_count = count_map_lines(data, *map_start);
	if (map_line_count <= 0)
	{
		printf("❌ Invalid map\n");
		return (FALSE);
	}
	data->map_width = get_map_width(data, *map_start);
	if (data->map_width <= 0)
	{
		printf("❌ Invalid map width\n");
		return (FALSE);
	}
	data->map_height = map_line_count;
	printf("📏 Map dimensions: %d x %d\n", data->map_width, data->map_height);
	return (TRUE);
}

int	allocate_map_memory(t_data *data)
{
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		printf("❌ Memory allocation error for map\n");
		return (FALSE);
	}
	return (TRUE);
}

char	*process_map_line(char *file_line)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(file_line);
	if (!trimmed_line)
	{
		printf("❌ Memory allocation error\n");
		return ((char *)-1);
	}
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (NULL);
	}
	return (trimmed_line);
}

int	add_line_to_map(t_data *data, char *trimmed_line, int map_index)
{
	char	*padded_line;

	padded_line = pad_map_line(trimmed_line, data->map_width);
	if (!padded_line)
		return (FALSE);
	data->map[map_index] = padded_line;
	printf("🗺️  Line %d: %s\n", map_index, data->map[map_index]);
	return (TRUE);
}
