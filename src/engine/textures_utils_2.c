/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:10 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 18:01:10 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_fallback_texture_properties(t_texture *texture)
{
	texture->width = TEXTURE_SIZE;
	texture->height = TEXTURE_SIZE;
	texture->mlx_texture = NULL;
}

static int	allocate_fallback_pixel_arrays(t_texture *texture)
{
	int	y;

	texture->pixels = malloc(sizeof(uint32_t *) * texture->height);
	if (!texture->pixels)
		return (FALSE);
	y = 0;
	while (y < texture->height)
	{
		texture->pixels[y] = malloc(sizeof(uint32_t) * texture->width);
		if (!texture->pixels[y])
		{
			while (--y >= 0)
				free(texture->pixels[y]);
			free(texture->pixels);
			return (FALSE);
		}
		y++;
	}
	return (TRUE);
}

static void	generate_checkerboard_row(t_texture *texture, int y, uint32_t color)
{
	int	x;

	x = 0;
	while (x < texture->width)
	{
		if ((x + y) % 8 < 4)
			texture->pixels[y][x] = color;
		else
			texture->pixels[y][x] = color - 0x40404000;
		x++;
	}
}

static int	create_fallback_texture(t_texture *texture, uint32_t color)
{
	int	y;

	init_fallback_texture_properties(texture);
	if (!allocate_fallback_pixel_arrays(texture))
		return (FALSE);
	y = 0;
	while (y < texture->height)
	{
		generate_checkerboard_row(texture, y, color);
		y++;
	}
	return (TRUE);
}

int	load_single_texture(t_data *data, int index)
{
	char		*texture_names[4];
	uint32_t	fallback_colors[4];

	texture_names[0] = "North";
	texture_names[1] = "South";
	texture_names[2] = "West";
	texture_names[3] = "East";
	fallback_colors[0] = 0xFF0000FF;
	fallback_colors[1] = 0x00FF00FF;
	fallback_colors[2] = 0x0000FFFF;
	fallback_colors[3] = 0xFFFF00FF;
	data->textures[index].mlx_texture = mlx_load_png(data->texture_paths[index]);
	if (!data->textures[index].mlx_texture)
	{
		if (!create_fallback_texture(&data->textures[index], fallback_colors[index]))
		{
			printf("❌ Failed to create fallback texture\n");
			return (FALSE);
		}
		printf("✅ %stexture created successfully\n", texture_names[index]);
		return (TRUE);
	}
	data->textures[index].width = data->textures[index].mlx_texture->width;
	data->textures[index].height = data->textures[index].mlx_texture->height;
	convert_texture_pixels(&data->textures[index]);
	if (!data->textures[index].pixels)
	{
		mlx_delete_texture(data->textures[index].mlx_texture);
		return (FALSE);
	}
	printf("✅ %s texture loaded successfully\n", texture_names[index]);
	return (TRUE);
}
