/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:34:47 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 22:41:14 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_trimmed_line(char **file_lines, int index)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(file_lines[index]);
	return (trimmed_line);
}

int	handle_line_processing_result(int result, char *trimmed_line)
{
	if (result == FALSE)
	{
		free(trimmed_line);
		return (FALSE);
	}
	if (result == -1)
	{
		free(trimmed_line);
		return (-1);
	}
	free(trimmed_line);
	return (TRUE);
}

int	process_single_line_with_cleanup(t_data *data, char *trimmed_line)
{
	int	result;

	if (is_empty_or_comment(trimmed_line))
	{
		free(trimmed_line);
		return (2);
	}
	result = process_single_line(data, trimmed_line);
	return (handle_line_processing_result(result, trimmed_line));
}
