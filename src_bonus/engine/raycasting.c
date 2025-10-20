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

#include "../../inc/cub3d.h"

void	init_ray(t_data *data, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;
	ray->pos.x = data->player_pos.x;
	ray->pos.y = data->player_pos.y;
	ray->dir.x = data->player_dir_vec.x + data->camera_plane.x * camera_x;
	ray->dir.y = data->player_dir_vec.y + data->camera_plane.y * camera_x;
	ray->map_x = (int)ray->pos.x;
	ray->map_y = (int)ray->pos.y;
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

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos.x 
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->wall_dist = (ray->map_y - ray->pos.y 
				+ (1 - ray->step.y) / 2) / ray->dir.y;
}

void	calculate_draw_bounds(t_ray *ray)
{
	calculate_line_height_and_bounds(ray);
	determine_texture_number(ray);
	calculate_texture_coordinates(ray);
}

void	cast_single_ray(t_data *data, int x)
{
	t_ray	ray;

	init_ray(data, &ray, x);
	calculate_step_and_side_dist(data, &ray);
	perform_dda(data, &ray);
	calculate_wall_distance(&ray);
	calculate_draw_bounds(&ray);
	draw_vertical_line(data, x, &ray);
}

void	cast_rays(t_data *data)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cast_single_ray(data, x);
		x++;
	}
}
