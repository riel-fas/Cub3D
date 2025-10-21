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

#include "../../inc/cub3d.h"

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

int	init_player(t_data *data)
{
	printf("🎮 Initializing player...\n");
	setup_player_vectors(data);
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
	if (!init_mlx(data))
		return (FALSE);
	if (!load_textures(data))
	{
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	printf("🧟 Initializing zombie animation...\n");
	if (!init_animation(&data->zombie_anim, "textures/zombie", 
			ZOMBIE_FRAME_RATE))
	{
		printf("❌ Failed to initialize zombie animation\n");
		cleanup_textures(data);
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	play_animation(&data->zombie_anim);
	if (!init_player(data))
	{
		cleanup_animation(&data->zombie_anim);
		cleanup_textures(data);
		mlx_terminate(data->mlx);
		return (FALSE);
	}
	printf("🚪 Initializing door system...\n");
	init_door_states(data);
	if (!load_door_texture(data))
	{
		printf("⚠️  Warning: Door texture loading had issues\n");
	}
	printf("🗺️  Initializing minimap...\n");
	init_minimap(data);
	mlx_key_hook(data->mlx, handle_input, data);
	mlx_cursor_hook(data->mlx, handle_mouse, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->game_running = TRUE;
	data->keys.w_pressed = 0;
	data->keys.a_pressed = 0;
	data->keys.s_pressed = 0;
	data->keys.d_pressed = 0;
	data->keys.left_pressed = 0;
	data->keys.right_pressed = 0;
	data->current_time = 0.0;
	printf("🎮 Use WASD to move, mouse to look, F to open doors, M to toggle minimap, ESC to exit\n\n");
	return (TRUE);
}
