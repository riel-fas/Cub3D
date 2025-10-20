/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:01:30 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/20 18:24:59 by riel-fas         ###   ########.fr       */
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
		&& data->map[map_y][map_x] != '1'
		&& !(data->map[map_y][map_x] == DOOR
			&& !is_door_open(data, map_x, map_y)))
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
		&& data->map[map_y][map_x] != '1'
		&& !(data->map[map_y][map_x] == DOOR
			&& !is_door_open(data, map_x, map_y)))
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
