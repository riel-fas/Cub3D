/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

static int	is_valid_char(char c)
{
	return (c == WALL || c == EMPTY || c == ' ' || is_player_char(c));
}

static int	find_player_position(t_data *data)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (is_player_char(data->map[y][x]))
			{
				data->player_x = (float)x + 0.5f;
				data->player_y = (float)y + 0.5f;
				data->player_dir = data->map[y][x];
				player_count++;
				printf("🎯 Player found at (%d, %d) facing %c\n", 
					   x, y, data->player_dir);
			}
			x++;
		}
		y++;
	}
	
	if (player_count == 0)
	{
		printf("❌ No player found in map\n");
		return (FALSE);
	}
	
	if (player_count > 1)
	{
		printf("❌ Multiple players found in map\n");
		return (FALSE);
	}
	
	return (TRUE);
}

static int	validate_characters(t_data *data)
{
	int	y;
	int	x;

	printf("🔍 Validating map characters...\n");
	
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (!is_valid_char(data->map[y][x]))
			{
				printf("❌ Invalid character '%c' (ASCII: %d) at position (%d, %d)\n", 
					   data->map[y][x], (int)data->map[y][x], x, y);
				return (FALSE);
			}
			x++;
		}
		y++;
	}
	
	printf("✅ All characters are valid\n");
	return (TRUE);
}

static int	check_map_borders(t_data *data)
{
	int	x, y;

	printf("🔒 Checking map borders...\n");
	
	// Check top and bottom borders
	for (x = 0; x < data->map_width; x++)
	{
		// Top border
		if (data->map[0][x] != WALL && data->map[0][x] != ' ')
		{
			printf("❌ Map not closed at top border (%d, 0)\n", x);
			return (FALSE);
		}
		// Bottom border
		if (data->map[data->map_height - 1][x] != WALL && 
			data->map[data->map_height - 1][x] != ' ')
		{
			printf("❌ Map not closed at bottom border (%d, %d)\n", x, data->map_height - 1);
			return (FALSE);
		}
	}
	
	// Check left and right borders
	for (y = 0; y < data->map_height; y++)
	{
		// Left border
		if (data->map[y][0] != WALL && data->map[y][0] != ' ')
		{
			printf("❌ Map not closed at left border (0, %d)\n", y);
			return (FALSE);
		}
		// Right border
		if (data->map[y][data->map_width - 1] != WALL && 
			data->map[y][data->map_width - 1] != ' ')
		{
			printf("❌ Map not closed at right border (%d, %d)\n", data->map_width - 1, y);
			return (FALSE);
		}
	}
	
	printf("✅ Map borders are properly closed\n");
	return (TRUE);
}

static int	check_empty_spaces_near_borders(t_data *data)
{
	int	x, y;

	printf("🚧 Checking spaces near borders...\n");
	
	for (y = 0; y < data->map_height; y++)
	{
		for (x = 0; x < data->map_width; x++)
		{
			if (data->map[y][x] == EMPTY || is_player_char(data->map[y][x]))
			{
				// Check if touching a space that touches border
				if ((x > 0 && data->map[y][x-1] == ' ') ||
					(x < data->map_width-1 && data->map[y][x+1] == ' ') ||
					(y > 0 && data->map[y-1][x] == ' ') ||
					(y < data->map_height-1 && data->map[y+1][x] == ' '))
				{
					// Check if that space reaches a border
					if (x == 0 || x == data->map_width-1 || y == 0 || y == data->map_height-1)
					{
						printf("❌ Empty space connects to border at (%d, %d)\n", x, y);
						return (FALSE);
					}
				}
			}
		}
	}
	
	printf("✅ No empty spaces connect to borders\n");
	return (TRUE);
}

static int	is_surrounded_by_walls(t_data *data, int x, int y)
{
	// Check if position is at border
	if (x == 0 || x == data->map_width - 1 || 
		y == 0 || y == data->map_height - 1)
	{
		return (data->map[y][x] == WALL);
	}
	
	// Check adjacent cells for walls or spaces that touch borders
	int	dx[] = {-1, 1, 0, 0};
	int	dy[] = {0, 0, -1, 1};
	int	i;
	int	nx, ny;

	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		
		// Check bounds
		if (nx < 0 || nx >= data->map_width || 
			ny < 0 || ny >= data->map_height)
		{
			return (FALSE);
		}
		
		// If adjacent to space, check if that space reaches border
		if (data->map[ny][nx] == ' ')
		{
			if (nx == 0 || nx == data->map_width - 1 || 
				ny == 0 || ny == data->map_height - 1)
			{
				return (FALSE);
			}
		}
		
		i++;
	}
	
	return (TRUE);
}

static int	validate_walls(t_data *data)
{
	int	y;
	int	x;

	printf("🧱 Validating walls...\n");
	
	// Check that all playable areas are surrounded by walls
	y = 0;
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

static void	flood_fill(char **map_copy, int x, int y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	
	if (map_copy[y][x] == WALL || map_copy[y][x] == 'F' || map_copy[y][x] == ' ')
		return;
	
	map_copy[y][x] = 'F';  // Mark as filled
	
	// Recursively fill adjacent cells
	flood_fill(map_copy, x + 1, y, width, height);
	flood_fill(map_copy, x - 1, y, width, height);
	flood_fill(map_copy, x, y + 1, width, height);
	flood_fill(map_copy, x, y - 1, width, height);
}

static int	flood_fill_validation(t_data *data)
{
	char	**map_copy;
	int		y;
	int		x;

	printf("🌊 Performing flood fill validation...\n");
	
	// Create a copy of the map
	map_copy = malloc(sizeof(char *) * data->map_height);
	if (!map_copy)
		return (FALSE);
	
	y = 0;
	while (y < data->map_height)
	{
		map_copy[y] = ft_strdup(data->map[y]);
		if (!map_copy[y])
		{
			while (--y >= 0)
				free(map_copy[y]);
			free(map_copy);
			return (FALSE);
		}
		y++;
	}
	
	// Start flood fill from player position
	flood_fill(map_copy, (int)data->player_x, (int)data->player_y, 
			   data->map_width, data->map_height);
	
	// Check if any empty space or player space was not reached (indicating disconnected areas)
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if ((data->map[y][x] == EMPTY || is_player_char(data->map[y][x])) && map_copy[y][x] != 'F')
			{
				printf("❌ Unreachable area found at (%d, %d)\n", x, y);
				// Free map copy
				y = 0;
				while (y < data->map_height)
					free(map_copy[y++]);
				free(map_copy);
				return (FALSE);
			}
			x++;
		}
		y++;
	}
	
	// Free map copy
	y = 0;
	while (y < data->map_height)
		free(map_copy[y++]);
	free(map_copy);
	
	printf("✅ Flood fill validation passed\n");
	return (TRUE);
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
