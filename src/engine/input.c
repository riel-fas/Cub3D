/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	// Calculate new position
	new_x = data->player_pos.x + move_x;
	new_y = data->player_pos.y + move_y;
	
	// Check x-axis collision
	map_x = (int)new_x;
	map_y = (int)data->player_pos.y;
	
	if (map_x >= 0 && map_x < data->map_width && 
		map_y >= 0 && map_y < data->map_height &&
		data->map[map_y][map_x] != '1')
	{
		data->player_pos.x = new_x;
		data->player_x = new_x;
	}
	
	// Check y-axis collision
	map_x = (int)data->player_pos.x;
	map_y = (int)new_y;
	
	if (map_x >= 0 && map_x < data->map_width && 
		map_y >= 0 && map_y < data->map_height &&
		data->map[map_y][map_x] != '1')
	{
		data->player_pos.y = new_y;
		data->player_y = new_y;
	}
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	// Update player angle
	data->player_angle += angle;
	data->player_angle = normalize_angle(data->player_angle);
	
	// Rotate direction vector
	old_dir_x = data->player_dir_vec.x;
	data->player_dir_vec.x = data->player_dir_vec.x * cos(angle) - 
							 data->player_dir_vec.y * sin(angle);
	data->player_dir_vec.y = old_dir_x * sin(angle) + 
							 data->player_dir_vec.y * cos(angle);
	
	// Rotate camera plane
	old_plane_x = data->camera_plane.x;
	data->camera_plane.x = data->camera_plane.x * cos(angle) - 
						   data->camera_plane.y * sin(angle);
	data->camera_plane.y = old_plane_x * sin(angle) + 
						   data->camera_plane.y * cos(angle);
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		data->game_running = FALSE;
		mlx_close_window(data->mlx);
		return;
	}
	
	// Update key states for smooth movement
	if (keydata.key == MLX_KEY_W)
		data->keys.w_pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) ? 1 : 0;
	else if (keydata.key == MLX_KEY_A)
		data->keys.a_pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) ? 1 : 0;
	else if (keydata.key == MLX_KEY_S)
		data->keys.s_pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) ? 1 : 0;
	else if (keydata.key == MLX_KEY_D)
		data->keys.d_pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) ? 1 : 0;
	else if (keydata.key == MLX_KEY_LEFT)
		data->keys.left_pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) ? 1 : 0;
	else if (keydata.key == MLX_KEY_RIGHT)
		data->keys.right_pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) ? 1 : 0;
}

void	handle_mouse(double xpos, double ypos, void *param)
{
	static double	last_x = -1;
	t_data			*data;
	double			delta_x;
	double			rotation;

	(void)ypos; // Suppress unused parameter warning
	data = (t_data *)param;
	
	// Initialize last_x on first call
	if (last_x == -1)
	{
		last_x = xpos;
		return;
	}
	
	// Calculate mouse movement
	delta_x = xpos - last_x;
	last_x = xpos;
	
	// Convert mouse movement to rotation
	rotation = delta_x * 0.002; // Sensitivity adjustment (increased for responsiveness)
	
	// Apply rotation
	if (fabs(rotation) > 0.0001) // Ignore tiny movements
		rotate_player(data, rotation);
}

void	process_movement(t_data *data)
{
	double	move_x;
	double	move_y;

	// Process movement based on key states
	if (data->keys.w_pressed)
	{
		move_x = data->player_dir_vec.x * MOVE_SPEED;
		move_y = data->player_dir_vec.y * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	if (data->keys.s_pressed)
	{
		move_x = -data->player_dir_vec.x * MOVE_SPEED;
		move_y = -data->player_dir_vec.y * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	if (data->keys.a_pressed)
	{
		// Strafe left (perpendicular to direction)
		move_x = data->player_dir_vec.y * MOVE_SPEED;
		move_y = -data->player_dir_vec.x * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	if (data->keys.d_pressed)
	{
		// Strafe right (perpendicular to direction)
		move_x = -data->player_dir_vec.y * MOVE_SPEED;
		move_y = data->player_dir_vec.x * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	
	// Process rotation
	if (data->keys.left_pressed)
		rotate_player(data, -ROTATE_SPEED);
	if (data->keys.right_pressed)
		rotate_player(data, ROTATE_SPEED);
}
