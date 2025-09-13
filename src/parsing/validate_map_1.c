/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:51:45 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 00:07:34 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_surrounded_by_walls(t_data *data, int x, int y)
{
	if (x == 0 || x == data->map_width - 1 || 
		y == 0 || y == data->map_height - 1)
		return (data->map[y][x] == WALL);
	int	dx[] = {-1, 1, 0, 0};
	int	dy[] = {0, 0, -1, 1};
	int	i;
	int	nx, ny;

	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx < 0 || nx >= data->map_width || 
			ny < 0 || ny >= data->map_height)
			return (FALSE);
		if (data->map[ny][nx] == ' ')
		{
			if (nx == 0 || nx == data->map_width - 1 || 
				ny == 0 || ny == data->map_height - 1)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	validate_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	printf("🧱 Validating walls...\n");
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			// If it's an empty space or player position
			if (data->map[y][x] == EMPTY || is_player_char(data->map[y][x]))
			{
				if (!is_surrounded_by_walls(data, x, y))
				{
					printf("❌ Map is not properly enclosed at (%d, %d)\n", x, y);
					return (FALSE);
				}
			}
			x++;
		}
		y++;
	}
	printf("✅ Map is properly enclosed by walls\n");
	return (TRUE);
}

void	flood_fill(char **map_copy, int x, int y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	if (map_copy[y][x] == WALL || map_copy[y][x] == 'F' || map_copy[y][x] == ' ')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, width, height);
	flood_fill(map_copy, x - 1, y, width, height);
	flood_fill(map_copy, x, y + 1, width, height);
	flood_fill(map_copy, x, y - 1, width, height);
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
	flood_fill(map_copy, (int)data->player_x, (int)data->player_y, 
			   data->map_width, data->map_height);
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
			if ((data->map[y][x] == EMPTY || is_player_char(data->map[y][x])) && map_copy[y][x] != 'F')
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
