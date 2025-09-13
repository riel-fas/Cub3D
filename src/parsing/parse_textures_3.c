/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:36:49 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 21:40:53 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check for duplicate texture and store texture data
static int	store_texture_data(t_data *data, char *path, int type)
{
	if (data->textures_parsed[type])
	{
		printf("❌ Duplicate texture definition: %s\n", 
			   (type == NO) ? "NO" : (type == SO) ? "SO" : 
			   (type == WE) ? "WE" : "EA");
		return (FALSE);
	}
	data->texture_paths[type] = path;
	data->textures_parsed[type] = 1;
	printf("✅ Texture %s: %s\n", 
		   (type == NO) ? "NO" : (type == SO) ? "SO" : 
		   (type == WE) ? "WE" : "EA", path);
	return (TRUE);
}

// Validate texture file extension and accessibility
static int	validate_texture_file(char *path)
{
	int	fd;

	if (!validate_texture_extension(path))
	{
		printf("❌ Texture file must have .xpm extension: %s\n", path);
		return (FALSE);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Cannot open texture file: %s\n", path);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

// Extract texture path from line, skipping identifier and whitespace
static char	*extract_texture_path(char *line, int type)
{
	char	*path;
	int		i;

	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
	{
		printf("❌ No texture path found for %s\n", 
			   (type == NO) ? "NO" : (type == SO) ? "SO" : 
			   (type == WE) ? "WE" : "EA");
		return (NULL);
	}
	path = ft_strtrim(&line[i]);
	if (!path)
		return (NULL);
	return (path);
}

// skip texture identifier and spaces
// Validate .xpm extension
// Check if file exists
// Check if texture already set
int	parse_texture_line(t_data *data, char *line)
{
	int		type;
	char	*path;

	type = get_texture_type(line);
	if (type == -1)
		return (FALSE);
	
	path = extract_texture_path(line, type);
	if (!path)
		return (FALSE);
	
	if (!validate_texture_file(path))
	{
		free(path);
		return (FALSE);
	}
	
	if (!store_texture_data(data, path, type))
	{
		free(path);
		return (FALSE);
	}
	
	return (TRUE);
}
