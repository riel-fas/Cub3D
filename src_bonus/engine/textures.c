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
			(texture->mlx_texture->pixels[index] << 24) 
			| (texture->mlx_texture->pixels[index + 1] << 16) 
			| (texture->mlx_texture->pixels[index + 2] << 8) 
			| texture->mlx_texture->pixels[index + 3];
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
