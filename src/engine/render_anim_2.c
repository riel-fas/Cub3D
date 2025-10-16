/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_anim_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:42:22 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:42:40 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_zombie_hud_position(int *hud_x, int *hud_y, int hud_size, int position_mode)
{
	if (position_mode == 1)
	{
		*hud_x = ZOMBIE_HUD_X_OFFSET;
		*hud_y = ZOMBIE_HUD_Y_OFFSET;
	}
	else if (position_mode == 2)
	{
		*hud_x = WINDOW_WIDTH - hud_size - ZOMBIE_HUD_X_OFFSET;
		*hud_y = ZOMBIE_HUD_Y_OFFSET;
	}
	else if (position_mode == 3)
	{
		*hud_x = ZOMBIE_HUD_X_OFFSET;
		*hud_y = WINDOW_HEIGHT - hud_size - ZOMBIE_HUD_Y_OFFSET;
	}
	else if (position_mode == 4)
	{
		*hud_x = (WINDOW_WIDTH - hud_size) / 2;
		*hud_y = (WINDOW_HEIGHT - hud_size) / 2;
	}
	else
	{
		*hud_x = WINDOW_WIDTH - hud_size - ZOMBIE_HUD_X_OFFSET;
		*hud_y = WINDOW_HEIGHT - hud_size - ZOMBIE_HUD_Y_OFFSET;
	}
}

void	render_frame(t_data *data)
{
	cast_rays(data);
	render_first_person_zombie_hands(data);
}