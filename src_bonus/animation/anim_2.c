/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:23:08 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/17 08:10:17 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	play_animation(t_animation *anim)
{
	anim->is_playing = 1;
	anim->last_update = 0.0;
}

void	pause_animation(t_animation *anim)
{
	anim->is_playing = 0;
}

void	reset_animation(t_animation *anim)
{
	anim->current_frame = 0;
	anim->last_update = 0.0;
}

t_texture	*get_current_frame(t_animation *anim)
{
	if (!anim->frames || anim->current_frame >= anim->frame_count)
		return (NULL);
	return (&anim->frames[anim->current_frame].texture);
}
