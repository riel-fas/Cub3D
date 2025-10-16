/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_texture_pixel(t_data *data, t_ray *ray, int y)
{
	int		tex_y;
	double	step;
	double	tex_pos;
	
	step = 1.0 * TEXTURE_SIZE / ray->line_height;
	tex_pos = (y - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
	return (get_pixel_color(&data->textures[ray->tex_num], ray->tex_x, tex_y));
}

void	draw_floor_and_ceiling(t_data *data, int x, t_ray *ray)
{
	int	y;

	for (y = 0; y < ray->draw_start; y++)
	{
		mlx_put_pixel(data->image, x, y, data->ceiling_color.hex);
	}
	for (y = ray->draw_end + 1; y < WINDOW_HEIGHT; y++)
	{
		mlx_put_pixel(data->image, x, y, data->floor_color.hex);
	}
}

void	draw_textured_wall(t_data *data, int x, t_ray *ray)
{
	int			y;
	uint32_t	color;

	for (y = ray->draw_start; y <= ray->draw_end; y++)
	{
		color = get_texture_pixel(data, ray, y);
		mlx_put_pixel(data->image, x, y, color);
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
