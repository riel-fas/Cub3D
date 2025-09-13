/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:31:37 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 00:31:40 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_surrounded_by_walls(t_data *data, int x, int y)
{
	int	dx[] = {-1, 1, 0, 0};
	int	dy[] = {0, 0, -1, 1};
	int	i;
	int	nx; 
	int	ny;

	i = 0;
	if (x == 0 || x == data->map_width - 1 || 
		y == 0 || y == data->map_height - 1)
		return (data->map[y][x] == WALL);
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx < 0 || nx >= data->map_width || ny < 0 || ny >= data->map_height)
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