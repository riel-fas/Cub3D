/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:39:36 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 02:21:00 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Initializes all texture paths and color values to default states
static void	init_textures_and_colors(t_data *data)
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
	data->colors_parsed[0] = 0;
	data->colors_parsed[1] = 0;
}


// Initializes map-related variables and player position to default values
static void	init_map_and_player(t_data *data)
{
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

// Calls all initialization functions to set up the data structure
static void	init_data(t_data *data)
{
	init_textures_and_colors(data);
	init_map_and_player(data);
}

// Validates that the filename has the correct .cub extension
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

// Displays texture parsing status with visual indicators (debug function)
static void	print_texture_status(t_data *data)
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
static void	print_color_status(t_data *data)
{
	printf("🎨 Colors: %d/2 ", data->colors_parsed[0] + data->colors_parsed[1]);
	if (data->colors_parsed[0] && data->colors_parsed[1])
		printf("✅\n");
	else
		printf("❌\n");
}

// Prints comprehensive summary of parsing results (debug function)
static void	print_parsing_summary(t_data *data)
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

// Main program entry point - handles argument validation and file parsing
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
	printf("🎯 Parsing completed successfully!\n");
	free_data(&data);
	return (EXIT_SUCCESS);
}
