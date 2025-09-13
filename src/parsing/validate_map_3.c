/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:34:37 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 23:34:39 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_borders(t_data *data)
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

int	check_empty_spaces_near_borders(t_data *data)
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