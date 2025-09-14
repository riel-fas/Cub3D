/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:58:39 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 01:03:54 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//helper function to open file and return file descriptor
static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_FILE);
	return (fd);
}

//helper function to read file content into a string
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

//helper function to split content into lines and count them
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

//reading the file lines 
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

//those printf's are only for debug should be removed after that
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
