/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:58:58 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 02:21:00 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Processes a single map line and adds it to the map array
int	process_map_line_index(t_data *data, int file_index, int *map_index)
{
	char	*trimmed_line;

	trimmed_line = process_map_line(data->file_lines[file_index]);
	if (trimmed_line == (char *)-1)
		return (FALSE);
	if (trimmed_line == NULL)
		return (TRUE);
	if (!add_line_to_map(data, trimmed_line, *map_index))
	{
		free(trimmed_line);
		return (FALSE);
	}
	free(trimmed_line);
	(*map_index)++;
	return (TRUE);
}

// Iterates through file lines and populates the map array
int	populate_map_data(t_data *data, int map_start)
{
	int	i;
	int	map_index;

	i = map_start;
	map_index = 0;
	while (i < data->line_count && map_index < data->map_height)
	{
		if (!process_map_line_index(data, i, &map_index))
			return (FALSE);
		i++;
	}
	data->map[map_index] = NULL;
	return (TRUE);
}

// Main map parsing function that coordinates map initialization and population
int	parse_map(t_data *data)
{
	int	map_start;

	if (!initialize_map_data(data, &map_start))
		return (FALSE);
	if (!allocate_map_memory(data))
		return (FALSE);
	if (!populate_map_data(data, map_start))
		return (FALSE);
	printf("✅ Map parsing completed\n");
	return (TRUE);
}
