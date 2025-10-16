/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:44:45 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 17:49:44 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_textured_wall(t_data *data, int x, t_ray *ray)
{
	int			y;
	uint32_t	color;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		color = get_texture_pixel(data, ray, y);
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	draw_floor_and_ceiling(data, x, ray);
	draw_textured_wall(data, x, ray);
}

void	render_frame(t_data *data)
{
	cast_rays(data);
}

void	update_game(t_data *data)
{
	data->player_pos.x = data->player_x;
	data->player_pos.y = data->player_y;
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->game_running)
		return ;
	process_movement(data);
	update_game(data);
	render_frame(data);
}
