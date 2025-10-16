/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:39:36 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 18:34:13 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Displays texture parsing status with visual indicators (debug function)
void	print_texture_status(t_data *data)
{
	int	total_textures;
	int	i;

	total_textures = 0;
	i = 0;
	while (i < 4)
	{
		if (data->textures_parsed[i])
			total_textures++;
		i++;
	}
	printf("️  Textures: %d/4 ", total_textures);
	if (total_textures == 4)
		printf("✅\n");
	else
		printf("❌\n");
}

// Displays color parsing status with visual indicators (debug function)
void	print_color_status(t_data *data)
{
	printf("🎨 Colors: %d/2 ", data->colors_parsed[0] + data->colors_parsed[1]);
	if (data->colors_parsed[0] && data->colors_parsed[1])
		printf("✅\n");
	else
		printf("❌\n");
}

// Prints comprehensive summary of parsing results (debug function)
void	print_parsing_summary(t_data *data)
{
	char	*filename;

	filename = "Unknown";
	if (data->filename)
		filename = data->filename;
	printf("\n🎯 === PARSING SUMMARY ===\n");
	printf("📁 File: %s\n", filename);
	printf("📄 Lines processed: %d\n", data->line_count);
	print_texture_status(data);
	print_color_status(data);
	printf("🗺️  Map: %dx%d ✅\n", data->map_width, data->map_height);
	printf("🎯 Player: (%.1f, %.1f) facing '%c' ✅\n",
		data->player_x, data->player_y, data->player_dir);
	printf("🎉 Status: PARSING COMPLETE! ✅\n");
	printf("========================\n\n");
}

// Handles argument validation and file parsing
static int	parse_and_validate(t_data *data, int argc, char **argv)
{
	if (argc != 2)
		error_exit(ERR_ARGS);
	if (!check_file_extension(argv[1]))
		error_exit(ERR_EXTENSION);
	init_data(data);
	data->filename = argv[1];
	printf("🚀 Starting Cub3D parsing...\n");
	printf("📁 File: %s\n\n", argv[1]);
	if (!parse_file(data, argv[1]))
	{
		printf("❌ Parsing failed!\n");
		free_data(data);
		exit(EXIT_FAILURE);
	}
	print_parsing_summary(data);
	printf("🎯 Parsing completed successfully!\n");
	return (TRUE);
}

// Main program entry point - coordinates parsing and game execution
int	main(int argc, char **argv)
{
	t_data	data;

	parse_and_validate(&data, argc, argv);
	printf("🎮 Starting 3D engine...\n");
	if (!init_game(&data))
	{
		printf("❌ Failed to initialize 3D engine!\n");
		free_data(&data);
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	cleanup_textures(&data);
	mlx_terminate(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
