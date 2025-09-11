/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += TWO_PI;
	while (angle >= TWO_PI)
		angle -= TWO_PI;
	return (angle);
}

double	distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	cleanup_game(t_data *data)
{
	if (!data)
		return;
	
	printf("🧹 Cleaning up game resources...\n");
	
	// Cleanup textures
	cleanup_textures(data);
	
	// Cleanup MLX
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	
	if (data->mlx)
		mlx_terminate(data->mlx);
	
	printf("✅ Game cleanup completed\n");
}
