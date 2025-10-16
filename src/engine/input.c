/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:39 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 17:08:38 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
