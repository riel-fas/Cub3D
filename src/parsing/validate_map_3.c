/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:34:37 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 00:42:52 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_horizontal_borders(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->map_width)
	{
		if (data->map[0][x] != WALL && data->map[0][x] != ' ')
		{
			printf("❌ Map not closed(%d, 0)\n", x);
			return (FALSE);
		}
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

int	check_vertical_borders(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		if (data->map[y][0] != WALL && data->map[y][0] != ' ')
		{
			printf("❌ Map not closed(0, %d)\n", y);
			return (FALSE);
		}
		if (data->map[y][data->map_width - 1] != WALL &&
			data->map[y][data->map_width - 1] != ' ')
		{
			printf("❌ Map not closed(%d, %d)\n", data->map_width - 1, y);
			return (FALSE);
		}
		y++;
	}
	return (TRUE);
}

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

int	is_space_connecting_to_border(t_data *data, int x, int y)
{
	if ((x > 0 && data->map[y][x - 1] == ' ')
		|| (x < data->map_width - 1 && data->map[y][x + 1] == ' ')
		|| (y > 0 && data->map[y - 1][x] == ' ')
		|| (y < data->map_height - 1 && data->map[y + 1][x] == ' '))
	{
		if (x == 0 || x == data->map_width - 1
			|| y == 0 || y == data->map_height - 1)
		{
			printf("❌ Empty space connects to border at (%d, %d)\n", x, y);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	check_empty_spaces_near_borders(t_data *data)
{
	int	x;
	int	y;

	printf("🚧 Checking spaces near borders...\n");
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
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
