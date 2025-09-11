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

#include "cub3d.h"

void	convert_texture_pixels(t_texture *texture)
{
	int	x, y;
	int	index;

	// Allocate 2D pixel array
	texture->pixels = malloc(sizeof(uint32_t *) * texture->height);
	if (!texture->pixels)
		return;
	
	for (y = 0; y < texture->height; y++)
	{
		texture->pixels[y] = malloc(sizeof(uint32_t) * texture->width);
		if (!texture->pixels[y])
		{
			// Free previously allocated rows
			while (--y >= 0)
				free(texture->pixels[y]);
			free(texture->pixels);
			texture->pixels = NULL;
			return;
		}
		
		for (x = 0; x < texture->width; x++)
		{
			// MLX42 uses RGBA format, 4 bytes per pixel
			index = (y * texture->width + x) * 4;
			texture->pixels[y][x] = 
				(texture->mlx_texture->pixels[index] << 24) |      // R
				(texture->mlx_texture->pixels[index + 1] << 16) |  // G
				(texture->mlx_texture->pixels[index + 2] << 8) |   // B
				texture->mlx_texture->pixels[index + 3];           // A
		}
	}
}

uint32_t	get_pixel_color(t_texture *texture, int x, int y)
{
	if (!texture || !texture->pixels || 
		x < 0 || x >= texture->width || 
		y < 0 || y >= texture->height)
		return (0xFF00FF00); // Magenta for errors
	
	return (texture->pixels[y][x]);
}

static int	create_fallback_texture(t_texture *texture, uint32_t color)
{
	int	x, y;

	texture->width = TEXTURE_SIZE;
	texture->height = TEXTURE_SIZE;
	texture->mlx_texture = NULL; // No MLX texture for fallback
	
	// Allocate pixel array
	texture->pixels = malloc(sizeof(uint32_t *) * texture->height);
	if (!texture->pixels)
		return (FALSE);
	
	for (y = 0; y < texture->height; y++)
	{
		texture->pixels[y] = malloc(sizeof(uint32_t) * texture->width);
		if (!texture->pixels[y])
		{
			while (--y >= 0)
				free(texture->pixels[y]);
			free(texture->pixels);
			return (FALSE);
		}
		
		for (x = 0; x < texture->width; x++)
		{
			// Create a simple pattern to make walls distinguishable
			if ((x + y) % 8 < 4)
				texture->pixels[y][x] = color;
			else
				texture->pixels[y][x] = color - 0x40404000; // Slightly darker
		}
	}
	
	return (TRUE);
}

int	load_single_texture(t_data *data, int index)
{
	char		*texture_names[] = {"North", "South", "West", "East"};
	uint32_t	fallback_colors[] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF};
	char		*png_path;
	int			path_len;
	
	printf("🖼️  Loading %s texture: %s\n", texture_names[index], 
		   data->texture_paths[index]);
	
	// Convert .xpm path to .png path for MLX42
	path_len = ft_strlen(data->texture_paths[index]);
	png_path = malloc(path_len + 1);
	if (!png_path)
		return (FALSE);
	
	// Copy the path and change extension from .xpm to .png
	strcpy(png_path, data->texture_paths[index]);
	if (path_len > 4 && ft_strncmp(png_path + path_len - 4, ".xpm", 4) == 0)
	{
		strcpy(png_path + path_len - 4, ".png");
	}
	
	data->textures[index].mlx_texture = mlx_load_png(png_path);
	free(png_path);
	
	if (!data->textures[index].mlx_texture)
	{
		printf("⚠️  PNG texture not found, creating fallback colored texture\n");
		
		// Create fallback colored texture
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
	
	printf("📏 Texture dimensions: %dx%d\n", 
		   data->textures[index].width, data->textures[index].height);
	
	// Convert texture to our pixel format
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

	printf("🎨 Loading textures...\n");
	
	// Initialize texture structures
	for (i = 0; i < 4; i++)
	{
		data->textures[i].mlx_texture = NULL;
		data->textures[i].pixels = NULL;
		data->textures[i].width = 0;
		data->textures[i].height = 0;
	}
	
	// Load all four textures
	for (i = 0; i < 4; i++)
	{
		if (!load_single_texture(data, i))
		{
			// Cleanup any loaded textures
			cleanup_textures(data);
			return (FALSE);
		}
	}
	
	printf("✅ All textures loaded successfully\n");
	return (TRUE);
}

void	cleanup_textures(t_data *data)
{
	int	i, y;

	for (i = 0; i < 4; i++)
	{
		// Free pixel arrays
		if (data->textures[i].pixels)
		{
			for (y = 0; y < data->textures[i].height; y++)
			{
				if (data->textures[i].pixels[y])
					free(data->textures[i].pixels[y]);
			}
			free(data->textures[i].pixels);
			data->textures[i].pixels = NULL;
		}
		
		// Free MLX textures
		if (data->textures[i].mlx_texture)
		{
			mlx_delete_texture(data->textures[i].mlx_texture);
			data->textures[i].mlx_texture = NULL;
		}
	}
}
