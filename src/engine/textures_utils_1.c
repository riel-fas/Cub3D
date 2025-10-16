/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:32:39 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 17:53:33 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_pixel_color(t_texture *texture, int x, int y)
{
	if (!texture || !texture->pixels || 
		x < 0 || x >= texture->width || 
		y < 0 || y >= texture->height)
		return (0xFF00FF00);
	return (texture->pixels[y][x]);
}

int	load_textures(t_data *data)
{
	int	i;

	i = 0;
	printf("🎨 Loading textures...\n");
	while (i < 4)
	{
		data->textures[i].mlx_texture = NULL;
		data->textures[i].pixels = NULL;
		data->textures[i].width = 0;
		data->textures[i].height = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!load_single_texture(data, i))
		{
			cleanup_textures(data);
			return (FALSE);
		}
		i++;
	}
	printf("✅ All textures loaded successfully\n");
	return (TRUE);
}

void	cleanup_textures(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i].pixels)
		{
			y = 0;
			while (y < data->textures[i].height)
			{
				if (data->textures[i].pixels[y])
					free(data->textures[i].pixels[y]);
				y++;
			}
			free(data->textures[i].pixels);
			data->textures[i].pixels = NULL;
		}
		if (data->textures[i].mlx_texture)
		{
			mlx_delete_texture(data->textures[i].mlx_texture);
			data->textures[i].mlx_texture = NULL;
		}
		i++;
	}
}
