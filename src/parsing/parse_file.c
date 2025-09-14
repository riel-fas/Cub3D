/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:58:39 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 02:21:00 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Opens a file in read-only mode and returns the file descriptor
static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_FILE);
	return (fd);
}

// Reads entire file content into a dynamically allocated string
static char	*read_file_content(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	int		total_size;
	char	*file_content;

	file_content = malloc(1);
	if (!file_content)
		error_exit(ERR_MALLOC);
	file_content[0] = '\0';
	total_size = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		file_content = realloc(file_content, total_size + bytes_read + 1);
		if (!file_content)
			error_exit(ERR_MALLOC);
		if (total_size == 0)
			file_content[0] = '\0';
		strcat(file_content, buffer);
		total_size += bytes_read;
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	}
	return (file_content);
}

// Splits file content into lines and counts the total number of lines
static char	**split_and_count_lines(char *file_content, int *line_count)
{
	char	**lines;

	lines = ft_split(file_content, '\n');
	if (!lines)
		error_exit(ERR_MALLOC);
	*line_count = 0;
	while (lines[*line_count])
		(*line_count)++;
	return (lines);
}

// Reads file and returns array of lines with line count
static char	**read_file_lines(char *filename, int *line_count)
{
	int		fd;
	char	**lines;
	char	*file_content;

	fd = open_file(filename);
	file_content = read_file_content(fd);
	close(fd);
	lines = split_and_count_lines(file_content, line_count);
	free(file_content);
	return (lines);
}

// Main parsing function that processes .cub file and validates all components
int	parse_file(t_data *data, char *filename)
{
	printf("📖 Reading file: %s\n", filename);
	data->file_lines = read_file_lines(filename, &data->line_count);
	printf("📝 File contains %d lines\n", data->line_count);
	printf("🎨 Parsing textures and colors...\n");
	if (!parse_textures_and_colors(data))
	{
		printf("❌ Failed to parse textures and colors\n");
		return (FALSE);
	}
	printf("🗺️  Parsing map...\n");
	if (!parse_map(data))
	{
		printf("❌ Failed to parse map\n");
		return (FALSE);
	}
	printf("✅ Validating map...\n");
	if (!validate_map(data))
	{
		printf("❌ Map validation failed\n");
		return (FALSE);
	}
	return (TRUE);
}
