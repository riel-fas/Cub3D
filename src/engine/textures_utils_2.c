/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:10 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 18:25:25 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	generate_checkerboard_row(t_texture *texture, int y, uint32_t color)
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

int	create_fallback_texture(t_texture *texture, uint32_t color)
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

int	handle_fallback_texture(t_data *data, int index)
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
	if (!create_fallback_texture(&data->textures[index], 
			fallback_colors[index]))
		return (FALSE);
	printf("✅ %s texture created successfully\n", texture_names[index]);
	return (TRUE);
}

int	load_single_texture(t_data *data, int index)
{
	char		*texture_names[4];

	texture_names[0] = "North";
	texture_names[1] = "South";
	texture_names[2] = "West";
	texture_names[3] = "East";
	data->textures[index].mlx_texture 
		= mlx_load_png(data->texture_paths[index]);
	if (!data->textures[index].mlx_texture)
		return (handle_fallback_texture(data, index));
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
