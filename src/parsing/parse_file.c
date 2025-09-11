/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**read_file_lines(char *filename, int *line_count)
{
	int		fd;
	char	**lines;
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	int		total_size;
	char	*file_content;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_FILE);
	
	// Read entire file into memory
	file_content = malloc(1);
	if (!file_content)
		error_exit(ERR_MALLOC);
	file_content[0] = '\0';
	total_size = 0;
	
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		file_content = realloc(file_content, total_size + bytes_read + 1);
		if (!file_content)
			error_exit(ERR_MALLOC);
		if (total_size == 0)
			file_content[0] = '\0';
		strcat(file_content, buffer);
		total_size += bytes_read;
	}
	close(fd);
	
	// Split content by newlines
	lines = ft_split(file_content, '\n');
	free(file_content);
	
	if (!lines)
		error_exit(ERR_MALLOC);
	
	// Count lines
	*line_count = 0;
	while (lines[*line_count])
		(*line_count)++;
	
	return (lines);
}

int	parse_file(t_data *data, char *filename)
{
	printf("📖 Reading file: %s\n", filename);
	
	// Read all lines from file
	data->file_lines = read_file_lines(filename, &data->line_count);
	
	printf("📝 File contains %d lines\n", data->line_count);
	
	// Parse textures and colors first
	printf("🎨 Parsing textures and colors...\n");
	if (!parse_textures_and_colors(data))
	{
		printf("❌ Failed to parse textures and colors\n");
		return (FALSE);
	}
	
	// Parse map
	printf("🗺️  Parsing map...\n");
	if (!parse_map(data))
	{
		printf("❌ Failed to parse map\n");
		return (FALSE);
	}
	
	// Validate map
	printf("✅ Validating map...\n");
	if (!validate_map(data))
	{
		printf("❌ Map validation failed\n");
		return (FALSE);
	}
	
	return (TRUE);
}
