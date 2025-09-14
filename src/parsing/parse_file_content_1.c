/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:51:14 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 01:44:22 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	iterate_through_lines(t_data *data)
{
	int		i;
	char	*trimmed_line;
	int		result;

	i = 0;
	while (i < data->line_count)
	{
		trimmed_line = get_trimmed_line(data->file_lines, i);
		if (!trimmed_line)
			return (FALSE);
		result = process_single_line_with_cleanup(data, trimmed_line);
		if (result == FALSE)
			return (FALSE);
		if (result == -1)
			break ;
		if (result == 2)
		{
			i++;
			continue ;
		}
		i++;
	}
	return (TRUE);
}

int	process_lines_until_map(t_data *data)
{
	return (iterate_through_lines(data));
}

int	parse_textures_and_colors(t_data *data)
{
	if (!process_lines_until_map(data))
		return (FALSE);
	return (validate_parsing_completeness(data));
}
