/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:51:45 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 00:49:37 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(char **map_copy, int x, int y, t_data *data)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return ;
	if (map_copy[y][x] == WALL || map_copy[y][x] == 'F'
		|| map_copy[y][x] == ' ')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, data);
	flood_fill(map_copy, x - 1, y, data);
	flood_fill(map_copy, x, y + 1, data);
	flood_fill(map_copy, x, y - 1, data);
}

char	**create_and_flood_fill_map(t_data *data)
{
	char	**map_copy;
	int		y;

	map_copy = malloc(sizeof(char *) * data->map_height);
	if (!map_copy)
		return (NULL);
	y = 0;
	while (y < data->map_height)
	{
		map_copy[y] = ft_strdup(data->map[y]);
		if (!map_copy[y])
		{
			while (--y >= 0)
				free(map_copy[y]);
			free(map_copy);
			return (NULL);
		}
		y++;
	}
	flood_fill(map_copy, (int)data->player_x, (int)data->player_y, data);
	return (map_copy);
}

int	validate_flood_fill_result(t_data *data, char **map_copy)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if ((data->map[y][x] == EMPTY || is_player_char(data->map[y][x]))
				&& map_copy[y][x] != 'F')
			{
				printf("❌ Unreachable area found at (%d, %d)\n", x, y);
				return (FALSE);
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

int	flood_fill_validation(t_data *data)
{
	char	**map_copy;
	int		y;
	int		result;

	printf("🌊 Performing flood fill validation...\n");
	map_copy = create_and_flood_fill_map(data);
	if (!map_copy)
		return (FALSE);
	result = validate_flood_fill_result(data, map_copy);
	y = 0;
	while (y < data->map_height)
		free(map_copy[y++]);
	free(map_copy);
	if (result)
		printf("✅ Flood fill validation passed\n");
	return (result);
}

int	validate_map(t_data *data)
{
	if (!validate_characters(data))
		return (FALSE);
	if (!find_player_position(data))
		return (FALSE);
	if (!check_map_borders(data))
		return (FALSE);
	if (!check_empty_spaces_near_borders(data))
		return (FALSE);
	if (!validate_walls(data))
		return (FALSE);
	if (!flood_fill_validation(data))
		return (FALSE);
	printf("✅ Map validation completed successfully\n");
	return (TRUE);
}
