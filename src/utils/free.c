/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return;
	
	// Free texture paths
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
	
	// Free map
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
	
	// Free file lines
	if (data->file_lines)
	{
		free_split(data->file_lines);
		data->file_lines = NULL;
	}
}
