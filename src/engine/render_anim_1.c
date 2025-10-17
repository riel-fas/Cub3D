/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_anim_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:40:47 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/17 09:21:49 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	calculate_hands_dimensions(int *hands_width, int *hands_height)
{
	*hands_width = WINDOW_WIDTH * FP_HANDS_WIDTH_SCALE;
	*hands_height = WINDOW_HEIGHT * FP_HANDS_HEIGHT_SCALE;
}

static void	calculate_hands_position(int hands_width, int hands_height, 
						int *hands_x, int *hands_y)
{
	*hands_x = (WINDOW_WIDTH - hands_width) / 2;
	*hands_y = WINDOW_HEIGHT - hands_height + FP_HANDS_Y_OFFSET;
}

static int	is_valid_pixel_position(t_pixel_coords coords, t_texture *texture)
{
	return (coords.tex_x >= 0 && coords.tex_x < texture->width
		&& coords.tex_y >= 0 && coords.tex_y < texture->height
		&& coords.screen_x < WINDOW_WIDTH && coords.screen_y < WINDOW_HEIGHT
		&& coords.screen_x >= 0 && coords.screen_y >= 0);
}

static void	render_hands_pixel(t_data *data, t_texture *current_frame,
								t_hands_render_info *info)
{
	t_pixel_coords	coords;
	uint32_t		color;

	coords.tex_x = (info->x * current_frame->width) / info->hands_width;
	coords.tex_y = (info->y * current_frame->height) / info->hands_height;
	coords.screen_x = info->hands_x + info->x;
	coords.screen_y = info->hands_y + info->y;
	if (is_valid_pixel_position(coords, current_frame))
	{
		color = get_pixel_color(current_frame, coords.tex_x, coords.tex_y);
		if ((color & 0xFF) != 0)
			mlx_put_pixel(data->image, coords.screen_x, coords.screen_y, color);
	}
}

void	render_first_person_zombie_hands(t_data *data)
{
	t_texture			*current_frame;
	t_hands_render_info	info;

	current_frame = get_current_frame(&data->zombie_anim);
	if (!current_frame)
		return ;
	calculate_hands_dimensions(&info.hands_width, &info.hands_height);
	calculate_hands_position(info.hands_width, info.hands_height, 
		&info.hands_x, &info.hands_y);
	info.y = 0;
	while (info.y < info.hands_height)
	{
		info.x = 0;
		while (info.x < info.hands_width)
		{
			render_hands_pixel(data, current_frame, &info);
			info.x++;
		}
		info.y++;
	}
}
