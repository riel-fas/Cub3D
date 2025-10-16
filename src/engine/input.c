/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:39 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 15:20:22 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_player_x(t_data *data, double move_x)
{
	double	new_x;
	int		map_x;
	int		map_y;

	new_x = data->player_pos.x + move_x;
	map_x = (int)(new_x + 0.1);
	if (move_x > 0)
		map_x = (int)(new_x + 0.2);
	else if (move_x < 0)
		map_x = (int)(new_x - 0.2);
	else
		map_x = (int)new_x;
	map_y = (int)data->player_pos.y;
	if (map_x >= 0 && map_x < data->map_width
		&& map_y >= 0 && map_y < data->map_height
		&& data->map[map_y] && data->map[map_y][map_x]
		&& data->map[map_y][map_x] != '1')
	{
		data->player_pos.x = new_x;
		data->player_x = new_x;
	}
}

void	move_player_y(t_data *data, double move_y)
{
	double	new_y;
	int		map_x;
	int		map_y;

	new_y = data->player_pos.y + move_y;
	map_x = (int)data->player_pos.x;
	map_y = (int)(new_y + 0.1);
	if (move_y > 0)
		map_y = (int)(new_y + 0.2);
	else if (move_y < 0)
		map_y = (int)(new_y - 0.2);
	else
		map_y = (int)new_y;
	if (map_x >= 0 && map_x < data->map_width
		&& map_y >= 0 && map_y < data->map_height
		&& data->map[map_y] && data->map[map_y][map_x]
		&& data->map[map_y][map_x] != '1')
	{
		data->player_pos.y = new_y;
		data->player_y = new_y;
	}
}

void	move_player(t_data *data, double move_x, double move_y)
{
	move_player_x(data, move_x);
	move_player_y(data, move_y);
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	data->player_angle += angle;
	data->player_angle = normalize_angle(data->player_angle);
	old_dir_x = data->player_dir_vec.x;
	data->player_dir_vec.x = data->player_dir_vec.x * cos(angle) - 
		data->player_dir_vec.y * sin(angle);
	data->player_dir_vec.y = old_dir_x * sin(angle) + 
		data->player_dir_vec.y * cos(angle);
	old_plane_x = data->camera_plane.x;
	data->camera_plane.x = data->camera_plane.x * cos(angle) - 
		data->camera_plane.y * sin(angle);
	data->camera_plane.y = old_plane_x * sin(angle) + 
		data->camera_plane.y * cos(angle);
}

void	handle_w_key(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		data->keys.w_pressed = 1;
	else
		data->keys.w_pressed = 0;
}

void	handle_a_key(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		data->keys.a_pressed = 1;
	else
		data->keys.a_pressed = 0;
}

void	handle_s_key(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		data->keys.s_pressed = 1;
	else
		data->keys.s_pressed = 0;
}

void	handle_d_key(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		data->keys.d_pressed = 1;
	else
		data->keys.d_pressed = 0;
}

void	handle_movement_keys(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_W)
		handle_w_key(keydata, data);
	else if (keydata.key == MLX_KEY_A)
		handle_a_key(keydata, data);
	else if (keydata.key == MLX_KEY_S)
		handle_s_key(keydata, data);
	else if (keydata.key == MLX_KEY_D)
		handle_d_key(keydata, data);
}

void	handle_rotation_keys(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			data->keys.left_pressed = 1;
		else
			data->keys.left_pressed = 0;
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			data->keys.right_pressed = 1;
		else
			data->keys.right_pressed = 0;
	}
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		data->game_running = FALSE;
		mlx_close_window(data->mlx);
		return ;
	}
	handle_movement_keys(keydata, data);
	handle_rotation_keys(keydata, data);
}

void	handle_mouse(double xpos, double ypos, void *param)
{
	static double	last_x = -1;
	t_data			*data;
	double			delta_x;
	double			rotation;

	(void)ypos;
	data = (t_data *)param;
	if (last_x == -1)
	{
		last_x = xpos;
		return;
	}
	delta_x = xpos - last_x;
	last_x = xpos;
	rotation = delta_x * 0.002;
	if (fabs(rotation) > 0.0001)
		rotate_player(data, rotation);
}

void	process_forward_backward(t_data *data)
{
	double	move_x;
	double	move_y;

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
}

void	process_strafe(t_data *data)
{
	double	move_x;
	double	move_y;

	if (data->keys.a_pressed)
	{
		move_x = data->player_dir_vec.y * MOVE_SPEED;
		move_y = -data->player_dir_vec.x * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	if (data->keys.d_pressed)
	{
		move_x = -data->player_dir_vec.y * MOVE_SPEED;
		move_y = data->player_dir_vec.x * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
}

void	process_rotation(t_data *data)
{
	if (data->keys.left_pressed)
		rotate_player(data, -ROTATE_SPEED);
	if (data->keys.right_pressed)
		rotate_player(data, ROTATE_SPEED);
}

void	process_movement(t_data *data)
{
	process_forward_backward(data);
	process_strafe(data);
	process_rotation(data);
}
