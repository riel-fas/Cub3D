/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/21 12:18:47 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Check if a pixel coordinate is within the minimap bounds
*/
int	is_pixel_in_minimap(t_data *data, int x, int y)
{
	return (x >= data->minimap.x_pos 
		&& x < data->minimap.x_pos + data->minimap.size
		&& y >= data->minimap.y_pos 
		&& y < data->minimap.y_pos + data->minimap.size);
}

/*
** Draw a single pixel on the minimap with bounds checking
*/
void	draw_minimap_pixel(t_data *data, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		if (is_pixel_in_minimap(data, x, y))
			mlx_put_pixel(data->image, x, y, color);
	}
}

/*
** Draw a single map tile on the minimap
*/
void	draw_minimap_tile(t_data *data, int map_x, int map_y, uint32_t color)
{
	int	screen_x;
	int	screen_y;
	int	dx;
	int	dy;
	int	tile_size;

	tile_size = data->minimap.tile_size;
	screen_x = data->minimap.x_pos + (int)((map_x - data->player_x) 
		* tile_size) + data->minimap.center_x;
	screen_y = data->minimap.y_pos + (int)((map_y - data->player_y) 
		* tile_size) + data->minimap.center_y;
	dy = 0;
	while (dy < tile_size)
	{
		dx = 0;
		while (dx < tile_size)
		{
			draw_minimap_pixel(data, screen_x + dx, screen_y + dy, color);
			dx++;
		}
		dy++;
	}
}

/*
** Draw all visible map tiles on the minimap
*/
void	draw_minimap_tiles(t_data *data)
{
	int			x;
	int			y;
	int			range;
	uint32_t	color;

	range = (data->minimap.size / data->minimap.tile_size) / 2 + 2;
	y = (int)data->player_y - range;
	while (y < (int)data->player_y + range)
	{
		x = (int)data->player_x - range;
		while (x < (int)data->player_x + range)
		{
			if (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
			{
				if (data->map[y][x] == '1')
					color = MINIMAP_WALL_COLOR;
				else if (data->map[y][x] == 'D')
					color = MINIMAP_DOOR_COLOR;
				else if (data->map[y][x] == '0' || data->map[y][x] == 'N' 
					|| data->map[y][x] == 'S' || data->map[y][x] == 'E' 
					|| data->map[y][x] == 'W')
					color = MINIMAP_FLOOR_COLOR;
				else
					color = MINIMAP_BG_COLOR;
				draw_minimap_tile(data, x, y, color);
			}
			x++;
		}
		y++;
	}
}

/*
** Draw the player as a circle/dot on the minimap
*/
void	draw_minimap_player(t_data *data)
{
	int		x;
	int		y;
	int		radius;
	int		dx;
	int		dy;
	int		center_x;
	int		center_y;

	radius = 3;
	center_x = data->minimap.x_pos + data->minimap.center_x;
	center_y = data->minimap.y_pos + data->minimap.center_y;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
			{
				x = center_x + dx;
				y = center_y + dy;
				draw_minimap_pixel(data, x, y, MINIMAP_PLAYER_COLOR);
			}
			dx++;
		}
		dy++;
	}
}

/*
** Draw direction rays on the minimap showing player's field of view
*/
void	draw_minimap_rays(t_data *data)
{
	double	ray_angle;
	double	ray_length;
	int		x;
	int		y;
	int		steps;
	int		i;
	int		center_x;
	int		center_y;

	center_x = data->minimap.x_pos + data->minimap.center_x;
	center_y = data->minimap.y_pos + data->minimap.center_y;
	ray_length = 20.0;
	steps = (int)ray_length;
	ray_angle = data->player_angle - FOV / 2;
	while (ray_angle <= data->player_angle + FOV / 2)
	{
		i = 0;
		while (i < steps)
		{
			x = center_x + (int)(cos(ray_angle) * i);
			y = center_y + (int)(sin(ray_angle) * i);
			draw_minimap_pixel(data, x, y, MINIMAP_RAY_COLOR);
			i++;
		}
		ray_angle += FOV / 20;
	}
}
