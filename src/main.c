/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture_paths[i] = NULL;
		data->textures_parsed[i] = 0;
		i++;
	}
	data->floor_color.r = -1;
	data->floor_color.g = -1;
	data->floor_color.b = -1;
	data->ceiling_color.r = -1;
	data->ceiling_color.g = -1;
	data->ceiling_color.b = -1;
	data->colors_parsed[0] = 0;	// Floor
	data->colors_parsed[1] = 0;	// Ceiling
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = 0;
	data->player_angle = 0;
	data->map_started = 0;
	data->parsing_complete = 0;
	data->file_lines = NULL;
	data->line_count = 0;
	data->filename = NULL;
	data->empty_lines_in_map = 0;
	data->visited = NULL;
}

static int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (FALSE);
	len = ft_strlen(filename);
	if (len < 4)
		return (FALSE);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (FALSE);
	return (TRUE);
}

static void	print_parsing_summary(t_data *data)
{
	int	total_textures = 0;
	int	i = 0;

	while (i < 4)
	{
		if (data->textures_parsed[i])
			total_textures++;
		i++;
	}

	printf("\n🎯 === PARSING SUMMARY ===\n");
	printf("📁 File: %s\n", data->filename ? data->filename : "Unknown");
	printf("📄 Lines processed: %d\n", data->line_count);
	printf("🖼️  Textures: %d/4 ", total_textures);
	if (total_textures == 4)
		printf("✅\n");
	else
		printf("❌\n");
	
	printf("🎨 Colors: %d/2 ", data->colors_parsed[0] + data->colors_parsed[1]);
	if (data->colors_parsed[0] && data->colors_parsed[1])
		printf("✅\n");
	else
		printf("❌\n");
	
	printf("🗺️  Map: %dx%d ✅\n", data->map_width, data->map_height);
	printf("🎯 Player: (%.1f, %.1f) facing '%c' ✅\n", 
		   data->player_x, data->player_y, data->player_dir);
	printf("🎉 Status: PARSING COMPLETE! ✅\n");
	printf("========================\n\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit(ERR_ARGS);
	
	if (!check_file_extension(argv[1]))
		error_exit(ERR_EXTENSION);
	
	init_data(&data);
	data.filename = argv[1];
	
	printf("🚀 Starting Cub3D parsing...\n");
	printf("📁 File: %s\n\n", argv[1]);
	
	if (!parse_file(&data, argv[1]))
	{
		printf("❌ Parsing failed!\n");
		free_data(&data);
		exit(EXIT_FAILURE);
	}
	
	print_parsing_summary(&data);
	
	// Initialize and start the 3D engine
	if (!init_game(&data))
	{
		printf("❌ Failed to initialize 3D engine!\n");
		free_data(&data);
		exit(EXIT_FAILURE);
	}
	
	// Start the game loop
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	
	// Cleanup
	cleanup_game(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
