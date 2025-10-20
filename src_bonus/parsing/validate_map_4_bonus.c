/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:31:37 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/25 18:24:28 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_directions(int dx[4], int dy[4])
{
	dx[0] = -1;
	dx[1] = 1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = -1;
	dy[3] = 1;
}

static int	check_adjacent_spaces(t_data *data, int nx, int ny)
{
	int	line_len;

	if (ny < 0 || ny >= data->map_height)
		return (FALSE);
	line_len = ft_strlen(data->map[ny]);
	if (nx < 0 || nx >= line_len)
		return (FALSE);
	if (data->map[ny][nx] == ' ')
	{
		if (nx == 0 || nx == line_len - 1
			|| ny == 0 || ny == data->map_height - 1)
			return (FALSE);
	}
	return (TRUE);
}

int	is_surrounded_by_walls(t_data *data, int x, int y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	line_len;

	init_directions(dx, dy);
	line_len = ft_strlen(data->map[y]);
	if (x == 0 || x == line_len - 1 || y == 0 || y == data->map_height - 1)
		return (data->map[y][x] == WALL);
	i = 0;
	while (i < 4)
	{
		if (!check_adjacent_spaces(data, x + dx[i], y + dy[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	validate_walls(t_data *data)
{
	int	y;
	int	x;
	int	line_len;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		line_len = ft_strlen(data->map[y]);
		while (x < line_len)
		{
			if (data->map[y][x] == EMPTY || is_player_char(data->map[y][x]))
			{
				if (!is_surrounded_by_walls(data, x, y))
				{
					printf("❌ Map is not enclosed(%d, %d)\n", x, y);
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
