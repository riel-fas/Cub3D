/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:30:40 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 17:52:19 by riel-fas         ###   ########.fr       */
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

	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(data->image, x, y, data->ceiling_color.hex);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(data->image, x, y, data->floor_color.hex);
		y++;
	}
}
