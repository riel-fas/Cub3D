/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:25:48 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 18:37:05 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Initializes all texture paths and color values to default states
void	init_textures_and_colors(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture_paths[i] = NULL;
		data->textures_parsed[i] = 0;
		i++;
	}
	data->floor_color.r = -1;
	data->floor_color.g = -1;
	data->floor_color.b = -1;
	data->ceiling_color.r = -1;
	data->ceiling_color.g = -1;
	data->ceiling_color.b = -1;
	data->colors_parsed[0] = 0;
	data->colors_parsed[1] = 0;
}

// Initializes map-related variables and player position 
//to default values
void	init_map_and_player(t_data *data)
{
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = 0;
	data->player_angle = 0;
	data->map_started = 0;
	data->parsing_complete = 0;
	data->file_lines = NULL;
	data->line_count = 0;
	data->filename = NULL;
	data->empty_lines_in_map = 0;
	data->visited = NULL;
}

// Calls all initialization functions to set up the data structure
void	init_data(t_data *data)
{
	init_textures_and_colors(data);
	init_map_and_player(data);
}

// Validates that the filename has the correct .cub extension
int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (FALSE);
	len = ft_strlen(filename);
	if (len < 4)
		return (FALSE);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (FALSE);
	return (TRUE);
}
