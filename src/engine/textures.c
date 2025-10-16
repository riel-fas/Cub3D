/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	allocate_pixel_arrays(t_texture *texture)
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
			texture->pixels = NULL;
			return (FALSE);
		}
		y++;
	}
	return (TRUE);
}

static void	convert_pixel_row(t_texture *texture, int y)
{
	int	x;
	int	index;

	x = 0;
	while (x < texture->width)
	{
		index = (y * texture->width + x) * 4;
		texture->pixels[y][x] = 
			(texture->mlx_texture->pixels[index] << 24) |
			(texture->mlx_texture->pixels[index + 1] << 16) |
			(texture->mlx_texture->pixels[index + 2] << 8) |
			texture->mlx_texture->pixels[index + 3];
		x++;
	}
}

void	convert_texture_pixels(t_texture *texture)
{
	int	y;

	if (!allocate_pixel_arrays(texture))
		return ;
	y = 0;
	while (y < texture->height)
	{
		convert_pixel_row(texture, y);
		y++;
	}
}

uint32_t	get_pixel_color(t_texture *texture, int x, int y)
{
	if (!texture || !texture->pixels || 
		x < 0 || x >= texture->width || 
		y < 0 || y >= texture->height)
		return (0xFF00FF00);
	
	return (texture->pixels[y][x]);
}

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
	char		*texture_names[] = {"North", "South", "West", "East"};
	uint32_t	fallback_colors[] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF};
	
	data->textures[index].mlx_texture = mlx_load_png(data->texture_paths[index]);
	if (!data->textures[index].mlx_texture)
	{
		if (!create_fallback_texture(&data->textures[index], fallback_colors[index]))
		{
			printf("❌ Failed to create fallback texture\n");
			return (FALSE);
		}
		printf("✅ %s fallback texture created successfully\n", texture_names[index]);
		return (TRUE);
	}
	data->textures[index].width = data->textures[index].mlx_texture->width;
	data->textures[index].height = data->textures[index].mlx_texture->height;
	convert_texture_pixels(&data->textures[index]);
	if (!data->textures[index].pixels)
	{
		printf("❌ Failed to convert texture pixels\n");
		mlx_delete_texture(data->textures[index].mlx_texture);
		return (FALSE);
	}
	printf("✅ %s texture loaded successfully\n", texture_names[index]);
	return (TRUE);
}

int	load_textures(t_data *data)
{
	int	i;

	i = 0;
	printf("🎨 Loading textures...\n");
	while(i < 4)
	{
		data->textures[i].mlx_texture = NULL;
		data->textures[i].pixels = NULL;
		data->textures[i].width = 0;
		data->textures[i].height = 0;
		i++;
	}
	i = 0;
	while(i < 4)
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
	int	i, y;

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
