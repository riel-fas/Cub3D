/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:34:37 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/25 13:14:47 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Checks that the top and bottom borders of the map are properly closed
int	check_horizontal_borders(t_data *data)
{
	int	x;
	int	top_len;
	int	bottom_len;

	// Check top border
	top_len = ft_strlen(data->map[0]);
	x = 0;
	while (x < top_len)
	{
		if (data->map[0][x] != WALL && data->map[0][x] != ' ')
		{
			printf("❌ Map not closed(%d, 0)\n", x);
			return (FALSE);
		}
		x++;
	}
	// Check bottom border
	bottom_len = ft_strlen(data->map[data->map_height - 1]);
	x = 0;
	while (x < bottom_len)
	{
		if (data->map[data->map_height - 1][x] != WALL &&
			data->map[data->map_height - 1][x] != ' ')
		{
			printf("❌ Map not closed(%d, %d)\n", x, data->map_height - 1);
			return (FALSE);
		}
		x++;
	}
	return (TRUE);
}

// Checks that the left and right borders of the map are properly closed
int	check_vertical_borders(t_data *data)
{
	int	y;
	int	line_len;

	y = 0;
	while (y < data->map_height)
	{
		line_len = ft_strlen(data->map[y]);
		if (line_len == 0)
		{
			y++;
			continue;
		}
		// Check left border
		if (data->map[y][0] != WALL && data->map[y][0] != ' ')
		{
			printf("❌ Map not closed(0, %d)\n", y);
			return (FALSE);
		}
		// Check right border (end of actual line, not padded width)
		if (data->map[y][line_len - 1] != WALL &&
			data->map[y][line_len - 1] != ' ')
		{
			printf("❌ Map not closed(%d, %d)\n", line_len - 1, y);
			return (FALSE);
		}
		y++;
	}
	return (TRUE);
}

// Validates that all map borders are properly closed with walls or spaces
int	check_map_borders(t_data *data)
{
	printf("🔒 Checking map borders...\n");
	if (!check_horizontal_borders(data))
		return (FALSE);
	if (!check_vertical_borders(data))
		return (FALSE);
	printf("✅ Map borders are properly closed\n");
	return (TRUE);
}

// Checks if an empty space is connecting 
// to the map border through adjacent spaces
int	is_space_connecting_to_border(t_data *data, int x, int y)
{
	int	line_len = ft_strlen(data->map[y]);
	
	// Check if this position is at the edge of the actual map content
	if (x == 0 || x == line_len - 1 || y == 0 || y == data->map_height - 1)
	{
		printf("❌ Empty space at border at (%d, %d)\n", x, y);
		return (TRUE);
	}
	
	// Check adjacent positions for spaces that could lead to borders
	if ((x > 0 && data->map[y][x - 1] == ' ')
		|| (x < line_len - 1 && data->map[y][x + 1] == ' ')
		|| (y > 0 && x < (int)ft_strlen(data->map[y - 1]) && data->map[y - 1][x] == ' ')
		|| (y < data->map_height - 1 && x < (int)ft_strlen(data->map[y + 1]) && data->map[y + 1][x] == ' '))
	{
		// If adjacent to a space, check if we're near a border
		if (x <= 1 || x >= line_len - 2 || y <= 1 || y >= data->map_height - 2)
		{
			printf("❌ Empty space connects to border through space at (%d, %d)\n", x, y);
			return (TRUE);
		}
	}
	return (FALSE);
}

// Validates that no empty spaces connect to map borders through adjacent spaces
int	check_empty_spaces_near_borders(t_data *data)
{
	int	x;
	int	y;
	int	line_len;

	printf("🚧 Checking spaces near borders...\n");
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if (data->map[y][x] == EMPTY || is_player_char(data->map[y][x]))
			{
				if (is_space_connecting_to_border(data, x, y))
					return (FALSE);
			}
			x++;
		}
		y++;
	}
	printf("✅ No empty spaces connect to borders\n");
	return (TRUE);
}
