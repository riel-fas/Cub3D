/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, t_ray *ray, int x)
{
	double	camera_x;

	// Calculate camera x coordinate (-1 to 1)
	camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;
	
	// Ray position = player position
	ray->pos.x = data->player_pos.x;
	ray->pos.y = data->player_pos.y;
	
	// Ray direction = player direction + camera plane offset
	ray->dir.x = data->player_dir_vec.x + data->camera_plane.x * camera_x;
	ray->dir.y = data->player_dir_vec.y + data->camera_plane.y * camera_x;
	
	// Current map position
	ray->map_x = (int)ray->pos.x;
	ray->map_y = (int)ray->pos.y;
	
	// Calculate delta distances
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_data *data, t_ray *ray)
{
	(void)data; // Suppress unused parameter warning
	
	// Calculate step and initial side_dist
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	}
	
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - ray->pos.y) * ray->delta_dist.y;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	// Perform DDA (Digital Differential Analyzer)
	while (ray->hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step.x;
			ray->side = 0; // x-side
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step.y;
			ray->side = 1; // y-side
		}
		
		// Check if ray has hit a wall
		if (ray->map_x < 0 || ray->map_x >= data->map_width ||
			ray->map_y < 0 || ray->map_y >= data->map_height ||
			data->map[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
		}
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	// Calculate distance to wall
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->wall_dist = (ray->map_y - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
}

void	calculate_draw_bounds(t_ray *ray)
{
	// Calculate height of line to draw on screen
	ray->line_height = (int)(WINDOW_HEIGHT / ray->wall_dist);
	
	// Calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
	
	// Determine texture number based on wall side and direction
	if (ray->side == 0) // x-side
	{
		if (ray->dir.x > 0)
			ray->tex_num = 3; // East texture
		else
			ray->tex_num = 2; // West texture
	}
	else // y-side
	{
		if (ray->dir.y > 0)
			ray->tex_num = 1; // South texture
		else
			ray->tex_num = 0; // North texture
	}
	
	// Calculate wall x coordinate for texture mapping
	if (ray->side == 0)
		ray->wall_x = ray->pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = ray->pos.x + ray->wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	
	// Calculate texture x coordinate
	ray->tex_x = (int)(ray->wall_x * (double)TEXTURE_SIZE);
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex_x = TEXTURE_SIZE - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex_x = TEXTURE_SIZE - ray->tex_x - 1;
}

void	cast_single_ray(t_data *data, int x)
{
	t_ray	ray;

	// Initialize ray
	init_ray(data, &ray, x);
	
	// Calculate step and side distances
	calculate_step_and_side_dist(data, &ray);
	
	// Perform DDA to find wall hit
	perform_dda(data, &ray);
	
	// Calculate wall distance and drawing bounds
	calculate_wall_distance(&ray);
	calculate_draw_bounds(&ray);
	
	// Draw the vertical line
	draw_vertical_line(data, x, &ray);
}

void	cast_rays(t_data *data)
{
	int	x;

	// Cast a ray for each column of pixels
	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		cast_single_ray(data, x);
	}
}
