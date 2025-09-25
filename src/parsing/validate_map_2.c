/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:33:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/25 13:14:47 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Checks if a character represents a player direction (N, S, E, W)
int	is_player_char(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

// Checks if a character is valid for the map (walls, empty, space, or player)
int	is_valid_char(char c)
{
	return (c == WALL || c == EMPTY || c == ' ' || is_player_char(c));
}

// Counts players in the map and sets player position data
int	count_and_set_player(t_data *data)
{
	int	y;
	int	x;
	int	player_count;
	int	line_len;

	player_count = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
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

// Validates that exactly one player exists in the map
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

// Validates that all characters in the map are valid 
// (walls, empty spaces, player)
int	validate_characters(t_data *data)
{
	int	y;
	int	x;
	int	line_len;

	printf("🔍 Validating map characters...\n");
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if (!is_valid_char(data->map[y][x]))
			{
				printf("❌Invalid'%c'(ASCII: %d) at position(%d, %d)\n",
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
