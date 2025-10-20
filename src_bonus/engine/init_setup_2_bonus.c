/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_setup_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:46:24 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 16:46:44 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	setup_player_direction_vectors(t_data *data)
{
	if (data->player_dir == 'N')
		setup_direction_north(data);
	else if (data->player_dir == 'S')
		setup_direction_south(data);
	else if (data->player_dir == 'E')
		setup_direction_east(data);
	else if (data->player_dir == 'W')
		setup_direction_west(data);
}

void	finalize_player_setup(t_data *data)
{
	data->player_angle = atan2(data->player_dir_vec.y, data->player_dir_vec.x);
	printf("🎯 Player setup: Pos(%.2f, %.2f) Dir(%.2f, %.2f) Angle(%.2f°)\n",
		data->player_pos.x, data->player_pos.y,
		data->player_dir_vec.x, data->player_dir_vec.y,
		data->player_angle * 180.0 / PI);
}

void	setup_player_vectors(t_data *data)
{
	setup_player_position(data);
	setup_player_direction_vectors(data);
	finalize_player_setup(data);
}
