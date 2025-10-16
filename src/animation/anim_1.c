/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:22:21 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:22:47 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	cleanup_animation_frames(t_animation *anim)
{
	int	i;

	if (!anim->frames)
		return ;
	i = 0;
	while (i < anim->frame_count)
	{
		cleanup_frame_texture(&anim->frames[i].texture);
		i++;
	}
	free(anim->frames);
	anim->frames = NULL;
}

void	cleanup_animation(t_animation *anim)
{
	cleanup_animation_frames(anim);
	if (anim->base_path)
	{
		free(anim->base_path);
		anim->base_path = NULL;
	}
	printf("🧹 Animation cleanup completed\n");
}