/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:28:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:28:36 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	allocate_animation_frames(t_animation *anim)
{
	printf("🎬 Loading %d animation frames...\n", anim->frame_count);
	anim->frames = malloc(sizeof(t_anim_frame) * anim->frame_count);
	if (!anim->frames)
	{
		printf("❌ Failed to allocate memory for animation frames\n");
		return (FALSE);
	}
	return (TRUE);
}

void	cleanup_partial_frames(t_animation *anim, int loaded_count)
{
	int	i;

	i = 0;
	while (i < loaded_count)
	{
		cleanup_frame_texture(&anim->frames[i].texture);
		i++;
	}
	free(anim->frames);
	anim->frames = NULL;
}

int	load_all_frames(t_animation *anim)
{
	int	i;

	i = 0;
	while (i < anim->frame_count)
	{
		if (!load_single_frame(anim, i))
		{
			cleanup_partial_frames(anim, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}