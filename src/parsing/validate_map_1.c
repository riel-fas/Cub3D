/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:51:45 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/20 18:24:58 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Recursively fills reachable areas starting from player position
void	flood_fill(char **map_copy, int x, int y, t_data *data)
{
	if (y < 0 || y >= data->map_height || x < 0)
		return ;
	if (x >= (int)ft_strlen(map_copy[y]))
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

// Creates a copy of the map and performs flood fill from player position
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

// Validates that all walkable areas are reachable from player position
int	validate_flood_fill_result(t_data *data, char **map_copy)
{
	int		y;
	int		x;
	int		line_len;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if ((data->map[y][x] == EMPTY || is_player_char(data->map[y][x])
					|| data->map[y][x] == DOOR)
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

// Coordinates flood fill validation and manages memory cleanup
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

// Main validation function that runs all 
//map validation checks (reference-style)
int	validate_map(t_data *data)
{
	if (!validate_characters(data))
		return (FALSE);
	if (!find_player_position(data))
		return (FALSE);
	if (!validate_map_boundaries(data))
		return (FALSE);
	printf("✅ Map validation completed successfully\n");
	return (TRUE);
}
