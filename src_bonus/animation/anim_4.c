/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:28:07 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:28:09 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	build_frame_path(char *frame_path, char *base_path, int frame_num)
{
	int	len;

	copy_base_path(frame_path, base_path, &len);
	add_frame_prefix(frame_path, len);
	add_frame_number(frame_path, len, frame_num);
}

int	load_frame_texture(t_texture *texture, char *frame_path)
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

int	setup_frame_pixels(t_texture *texture)
{
	convert_texture_pixels(texture);
	if (!texture->pixels)
	{
		mlx_delete_texture(texture->mlx_texture);
		return (FALSE);
	}
	return (TRUE);
}

int	load_single_frame(t_animation *anim, int frame_num)
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

void	cleanup_frame_texture(t_texture *texture)
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
