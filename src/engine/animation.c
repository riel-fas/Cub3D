/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:30:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:17:29 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	get_current_time(void)
{
	return (mlx_get_time());
}

static void	copy_base_path(char *frame_path, char *base_path, int *len)
{
	*len = ft_strlen(base_path);
	ft_strncpy(frame_path, base_path, *len);
}

static void	add_frame_prefix(char *frame_path, int len)
{
	frame_path[len] = '/';
	frame_path[len + 1] = 'f';
	frame_path[len + 2] = 'r';
	frame_path[len + 3] = 'a';
	frame_path[len + 4] = 'm';
	frame_path[len + 5] = 'e';
	frame_path[len + 6] = '_';
}

static void	add_frame_number(char *frame_path, int len, int frame_num)
{
	if (frame_num < 10)
	{
		frame_path[len + 7] = '0' + frame_num;
		frame_path[len + 8] = '.';
		frame_path[len + 9] = 'p';
		frame_path[len + 10] = 'n';
		frame_path[len + 11] = 'g';
		frame_path[len + 12] = '\0';
	}
	else
	{
		frame_path[len + 7] = '0' + (frame_num / 10);
		frame_path[len + 8] = '0' + (frame_num % 10);
		frame_path[len + 9] = '.';
		frame_path[len + 10] = 'p';
		frame_path[len + 11] = 'n';
		frame_path[len + 12] = 'g';
		frame_path[len + 13] = '\0';
	}
}

static void	build_frame_path(char *frame_path, char *base_path, int frame_num)
{
	int	len;

	copy_base_path(frame_path, base_path, &len);
	add_frame_prefix(frame_path, len);
	add_frame_number(frame_path, len, frame_num);
}

static int	load_frame_texture(t_texture *texture, char *frame_path)
{
	texture->mlx_texture = mlx_load_png(frame_path);
	if (!texture->mlx_texture)
	{
		printf("❌ Failed to load animation frame: %s\n", frame_path);
		return (FALSE);
	}
	texture->width = texture->mlx_texture->width;
	texture->height = texture->mlx_texture->height;
	return (TRUE);
}

static int	setup_frame_pixels(t_texture *texture)
{
	convert_texture_pixels(texture);
	if (!texture->pixels)
	{
		mlx_delete_texture(texture->mlx_texture);
		return (FALSE);
	}
	return (TRUE);
}

static int	load_single_frame(t_animation *anim, int frame_num)
{
	char	frame_path[512];

	build_frame_path(frame_path, anim->base_path, frame_num);
	anim->frames[frame_num].frame_number = frame_num;
	if (!load_frame_texture(&anim->frames[frame_num].texture, frame_path))
		return (FALSE);
	if (!setup_frame_pixels(&anim->frames[frame_num].texture))
		return (FALSE);
	printf("✅ Loaded frame %d: %s\n", frame_num, frame_path);
	return (TRUE);
}

static void	cleanup_frame_texture(t_texture *texture)
{
	int	y;

	if (texture->pixels)
	{
		y = 0;
		while (y < texture->height)
		{
			if (texture->pixels[y])
				free(texture->pixels[y]);
			y++;
		}
		free(texture->pixels);
		texture->pixels = NULL;
	}
	if (texture->mlx_texture)
	{
		mlx_delete_texture(texture->mlx_texture);
		texture->mlx_texture = NULL;
	}
}

static int	allocate_animation_frames(t_animation *anim)
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

static void	cleanup_partial_frames(t_animation *anim, int loaded_count)
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

static int	load_all_frames(t_animation *anim)
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
	printf("🎬 Initializing animation with %d frames, frame duration: %.3f seconds\n", 
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
