/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:44:45 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 20:59:32 by riel-fas         ###   ########.fr       */
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

void	calculate_zombie_hud_position(int *hud_x, int *hud_y, int hud_size, int position_mode)
{
	// Position modes:
	// 0 = bottom-right, 1 = top-left, 2 = top-right, 3 = bottom-left, 4 = center
	if (position_mode == 1) // top-left
	{
		*hud_x = ZOMBIE_HUD_X_OFFSET;
		*hud_y = ZOMBIE_HUD_Y_OFFSET;
	}
	else if (position_mode == 2) // top-right
	{
		*hud_x = WINDOW_WIDTH - hud_size - ZOMBIE_HUD_X_OFFSET;
		*hud_y = ZOMBIE_HUD_Y_OFFSET;
	}
	else if (position_mode == 3) // bottom-left
	{
		*hud_x = ZOMBIE_HUD_X_OFFSET;
		*hud_y = WINDOW_HEIGHT - hud_size - ZOMBIE_HUD_Y_OFFSET;
	}
	else if (position_mode == 4) // center
	{
		*hud_x = (WINDOW_WIDTH - hud_size) / 2;
		*hud_y = (WINDOW_HEIGHT - hud_size) / 2;
	}
	else // default: bottom-right (position_mode == 0)
	{
		*hud_x = WINDOW_WIDTH - hud_size - ZOMBIE_HUD_X_OFFSET;
		*hud_y = WINDOW_HEIGHT - hud_size - ZOMBIE_HUD_Y_OFFSET;
	}
}

void	render_first_person_zombie_hands(t_data *data)
{
	t_texture	*current_frame;
	int			hands_width;
	int			hands_height;
	int			hands_x;
	int			hands_y;
	int			x;
	int			y;
	uint32_t	color;

	current_frame = get_current_frame(&data->zombie_anim);
	if (!current_frame)
		return;

	// First-person hands configuration using defines
	hands_width = WINDOW_WIDTH * FP_HANDS_WIDTH_SCALE;
	hands_height = WINDOW_HEIGHT * FP_HANDS_HEIGHT_SCALE;
	
	// Position hands in bottom-center of screen (like FPS games)
	hands_x = (WINDOW_WIDTH - hands_width) / 2;      // Center horizontally
	hands_y = WINDOW_HEIGHT - hands_height + FP_HANDS_Y_OFFSET;  // Bottom position

	// Draw the zombie hands scaled to first-person size
	y = 0;
	while (y < hands_height)
	{
		x = 0;
		while (x < hands_width)
		{
			// Map screen coordinates to texture coordinates
			int tex_x = (x * current_frame->width) / hands_width;
			int tex_y = (y * current_frame->height) / hands_height;
			
			// Check bounds
			if (tex_x >= 0 && tex_x < current_frame->width && 
				tex_y >= 0 && tex_y < current_frame->height &&
				hands_x + x < WINDOW_WIDTH && hands_y + y < WINDOW_HEIGHT &&
				hands_x + x >= 0 && hands_y + y >= 0)
			{
				color = get_pixel_color(current_frame, tex_x, tex_y);
				// Skip transparent pixels (alpha channel check)
				if ((color & 0xFF) != 0)
					mlx_put_pixel(data->image, hands_x + x, hands_y + y, color);
			}
			x++;
		}
		y++;
	}
}

void	render_frame(t_data *data)
{
	cast_rays(data);
	render_first_person_zombie_hands(data);
}

void	update_game(t_data *data)
{
	data->player_pos.x = data->player_x;
	data->player_pos.y = data->player_y;
	
	// Update current time and animations
	data->current_time = get_current_time();
	update_animation(&data->zombie_anim, data->current_time);
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
