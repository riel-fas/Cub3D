/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:40:05 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/20 18:24:58 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Frees a null-terminated array of strings
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// Frees all allocated texture path strings
static void	free_texture_paths(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture_paths[i])
		{
			free(data->texture_paths[i]);
			data->texture_paths[i] = NULL;
		}
		i++;
	}
}

// Frees the 2D map array and all its rows
static void	free_map_data(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->map_height && data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
}

// Main cleanup function that frees all allocated memory in the data structure
void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_texture_paths(data);
	free_map_data(data);
	free_door_states(data);
	cleanup_animation(&data->zombie_anim);
	if (data->file_lines)
	{
		free_split(data->file_lines);
		data->file_lines = NULL;
	}
}
