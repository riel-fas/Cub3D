/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:00:00 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/20 18:24:58 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Initialize door states array - tracks which doors are open (1) or closed (0)
void	init_door_states(t_data *data)
{
	int	y;
	int	x;

	data->door_states = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->door_states)
		error_exit(ERR_MALLOC);
	y = 0;
	while (y < data->map_height)
	{
		data->door_states[y] = malloc(sizeof(char) * (data->map_width + 1));
		if (!data->door_states[y])
		{
			while (--y >= 0)
				free(data->door_states[y]);
			free(data->door_states);
			error_exit(ERR_MALLOC);
		}
		x = 0;
		while (x < data->map_width)
		{
			data->door_states[y][x] = '0';
			x++;
		}
		data->door_states[y][x] = '\0';
		y++;
	}
	data->door_states[y] = NULL;
}

// Free door states memory
void	free_door_states(t_data *data)
{
	int	y;

	if (!data->door_states)
		return ;
	y = 0;
	while (y < data->map_height)
	{
		free(data->door_states[y]);
		y++;
	}
	free(data->door_states);
	data->door_states = NULL;
}

// Check if a door at position (x, y) is open
int	is_door_open(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map_height || x < 0 || x >= data->map_width)
		return (0);
	if (!data->door_states)
		return (0);
	return (data->door_states[y][x] == '1');
}

// Toggle door in front of player (open if closed, close if open)
void	toggle_door(t_data *data)
{
	int		door_x;
	int		door_y;
	double	check_dist;

	check_dist = 1.5;
	door_x = (int)(data->player_pos.x + data->player_dir_vec.x * check_dist);
	door_y = (int)(data->player_pos.y + data->player_dir_vec.y * check_dist);
	if (door_x < 0 || door_x >= data->map_width
		|| door_y < 0 || door_y >= data->map_height)
		return ;
	if (data->map[door_y][door_x] == DOOR)
	{
		if (data->door_states[door_y][door_x] == '0')
		{
			data->door_states[door_y][door_x] = '1';
			printf("🚪 Door opened at (%d, %d)\n", door_x, door_y);
		}
		else
		{
			data->door_states[door_y][door_x] = '0';
			printf("🚪 Door closed at (%d, %d)\n", door_x, door_y);
		}
	}
}

// Load door texture from file
int	load_door_texture(t_data *data)
{
	mlx_texture_t	*mlx_tex;
	int				y;
	int				x;

	mlx_tex = mlx_load_png("./textures/door/DOOR_4A.PNG");
	if (!mlx_tex)
	{
		printf("⚠️  Warning: Could not load door texture, using fallback\n");
		return (create_fallback_texture(&data->door_texture, 0x8B4513FF));
	}
	data->door_texture.mlx_texture = mlx_tex;
	data->door_texture.width = mlx_tex->width;
	data->door_texture.height = mlx_tex->height;
	data->door_texture.pixels = malloc(sizeof(uint32_t *)
			* data->door_texture.height);
	if (!data->door_texture.pixels)
	{
		mlx_delete_texture(mlx_tex);
		return (FALSE);
	}
	y = 0;
	while (y < data->door_texture.height)
	{
		data->door_texture.pixels[y] = malloc(sizeof(uint32_t)
				* data->door_texture.width);
		if (!data->door_texture.pixels[y])
		{
			while (--y >= 0)
				free(data->door_texture.pixels[y]);
			free(data->door_texture.pixels);
			mlx_delete_texture(mlx_tex);
			return (FALSE);
		}
		x = 0;
		while (x < data->door_texture.width)
		{
			data->door_texture.pixels[y][x] = ((uint32_t *)mlx_tex->pixels)
				[y * data->door_texture.width + x];
			x++;
		}
		y++;
	}
	mlx_delete_texture(mlx_tex);
	printf("✅ Door texture loaded successfully\n");
	return (TRUE);
}
