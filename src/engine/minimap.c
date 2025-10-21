/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/21 12:18:47 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Initialize minimap structure with default values
*/
void	init_minimap(t_data *data)
{
	data->minimap.visible = 1;
	data->minimap.x_pos = MINIMAP_X_OFFSET;
	data->minimap.y_pos = MINIMAP_Y_OFFSET;
	data->minimap.size = MINIMAP_SIZE;
	data->minimap.tile_size = MINIMAP_TILE_SIZE;
	data->minimap.center_x = data->minimap.size / 2;
	data->minimap.center_y = data->minimap.size / 2;
	data->minimap.scale = 1.0;
}

/*
** Toggle minimap visibility on/off
*/
void	toggle_minimap(t_data *data)
{
	data->minimap.visible = !data->minimap.visible;
}

/*
** Draw a filled rectangle for minimap background
*/
void	draw_minimap_background(t_data *data)
{
	int	x;
	int	y;

	y = data->minimap.y_pos;
	while (y < data->minimap.y_pos + data->minimap.size)
	{
		x = data->minimap.x_pos;
		while (x < data->minimap.x_pos + data->minimap.size)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				mlx_put_pixel(data->image, x, y, MINIMAP_BG_COLOR);
			x++;
		}
		y++;
	}
}

/*
** Main minimap rendering function
*/
void	render_minimap(t_data *data)
{
	if (!data->minimap.visible)
		return ;
	draw_minimap_background(data);
	draw_minimap_tiles(data);
	draw_minimap_rays(data);
	draw_minimap_player(data);
}
