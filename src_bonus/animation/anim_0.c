/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:30:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/17 08:09:52 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_animation_frames(t_animation *anim)
{
	if (!allocate_animation_frames(anim))
		return (FALSE);
	if (!load_all_frames(anim))
		return (FALSE);
	printf("✅ All %d animation frames loaded successfully\n", anim->frame_count);
	return (TRUE);
}

int	init_animation(t_animation *anim, char *base_path, double frame_duration)
{
	anim->frames = NULL;
	anim->frame_count = 57;
	anim->current_frame = 0;
	anim->frame_duration = frame_duration;
	anim->last_update = 0.0;
	anim->is_playing = 0;
	anim->loop = 1;
	anim->base_path = ft_strdup(base_path);
	if (!anim->base_path)
	{
		printf("❌ Failed to duplicate base path for animation\n");
		return (FALSE);
	}
	printf("🎬 %d frames,frame duration: %.3f seconds\n", 
		anim->frame_count, frame_duration);
	return (load_animation_frames(anim));
}

void	update_animation(t_animation *anim, double current_time)
{
	if (!anim->is_playing || !anim->frames)
		return ;
	if (anim->last_update == 0.0)
		anim->last_update = current_time;
	if (current_time - anim->last_update >= anim->frame_duration)
	{
		anim->current_frame++;
		if (anim->current_frame >= anim->frame_count)
		{
			if (anim->loop)
				anim->current_frame = 0;
			else
			{
				anim->current_frame = anim->frame_count - 1;
				anim->is_playing = 0;
			}
		}
		anim->last_update = current_time;
	}
}
