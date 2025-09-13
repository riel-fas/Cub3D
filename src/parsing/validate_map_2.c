/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:33:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 00:00:17 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

int	is_valid_char(char c)
{
	return (c == WALL || c == EMPTY || c == ' ' || is_player_char(c));
}

int	count_and_set_player(t_data *data)
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
	return (player_count);
}

int	find_player_position(t_data *data)
{
	int	player_count;

	player_count = count_and_set_player(data);
	
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

int	validate_characters(t_data *data)
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
