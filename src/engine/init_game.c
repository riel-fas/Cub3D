/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_data *data)
{
	printf("🖥️  Initializing MLX42...\n");
	
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (!data->mlx)
	{
		printf("❌ Failed to initialize MLX42\n");
		return (FALSE);
	}
	
	data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->image)
	{
		printf("❌ Failed to create MLX image\n");
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		printf("❌ Failed to display image\n");
		mlx_delete_image(data->mlx, data->image);
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	
	printf("✅ MLX42 initialized successfully\n");
	return (TRUE);
}

void	setup_player_vectors(t_data *data)
{
	// Convert player position to double precision
	data->player_pos.x = data->player_x;
	data->player_pos.y = data->player_y;
	
	// Set direction vector based on player direction character
	if (data->player_dir == 'N')
	{
		data->player_dir_vec.x = 0.0;
		data->player_dir_vec.y = -1.0;
		data->camera_plane.x = 0.66;  // FOV control
		data->camera_plane.y = 0.0;
	}
	else if (data->player_dir == 'S')
	{
		data->player_dir_vec.x = 0.0;
		data->player_dir_vec.y = 1.0;
		data->camera_plane.x = -0.66;
		data->camera_plane.y = 0.0;
	}
	else if (data->player_dir == 'E')
	{
		data->player_dir_vec.x = 1.0;
		data->player_dir_vec.y = 0.0;
		data->camera_plane.x = 0.0;
		data->camera_plane.y = 0.66;
	}
	else if (data->player_dir == 'W')
	{
		data->player_dir_vec.x = -1.0;
		data->player_dir_vec.y = 0.0;
		data->camera_plane.x = 0.0;
		data->camera_plane.y = -0.66;
	}
	
	// Calculate player angle from direction vector
	data->player_angle = atan2(data->player_dir_vec.y, data->player_dir_vec.x);
	
	printf("🎯 Player setup: Pos(%.2f, %.2f) Dir(%.2f, %.2f) Angle(%.2f°)\n",
		   data->player_pos.x, data->player_pos.y,
		   data->player_dir_vec.x, data->player_dir_vec.y,
		   data->player_angle * 180.0 / PI);
}

int	init_player(t_data *data)
{
	printf("🎮 Initializing player...\n");
	
	setup_player_vectors(data);
	
	// Convert RGB colors to hex for MLX
	data->floor_color.hex = rgb_to_hex(data->floor_color.r, 
									   data->floor_color.g, 
									   data->floor_color.b);
	data->ceiling_color.hex = rgb_to_hex(data->ceiling_color.r, 
										 data->ceiling_color.g, 
										 data->ceiling_color.b);
	
	printf("✅ Player initialized successfully\n");
	return (TRUE);
}

int	init_game(t_data *data)
{
	printf("\n🚀 Initializing 3D Engine...\n");
	
	// Initialize MLX
	if (!init_mlx(data))
		return (FALSE);
	
	// Load textures
	if (!load_textures(data))
	{
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	
	// Initialize player
	if (!init_player(data))
	{
		cleanup_textures(data);
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	
	// Set up input callbacks
	mlx_key_hook(data->mlx, handle_input, data);
	mlx_cursor_hook(data->mlx, handle_mouse, data);
	
	// Set game state
	data->game_running = TRUE;
	
	// Initialize key states
	data->keys.w_pressed = 0;
	data->keys.a_pressed = 0;
	data->keys.s_pressed = 0;
	data->keys.d_pressed = 0;
	data->keys.left_pressed = 0;
	data->keys.right_pressed = 0;
	
	printf("🎉 3D Engine initialized successfully!\n");
	printf("🎮 Use WASD to move, mouse to look around, ESC to exit\n\n");
	
	return (TRUE);
}
