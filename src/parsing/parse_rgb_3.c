/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:26:01 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 22:45:10 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check if color already set
// Skip spaces
static int	identify_color_type(char *line, t_color **target_color, 
						char **type_name, int **color_flag, t_data *data)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		*target_color = &data->floor_color;
		*type_name = "Floor";
		*color_flag = &data->colors_parsed[0];
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		*target_color = &data->ceiling_color;
		*type_name = "Ceiling";
		*color_flag = &data->colors_parsed[1];
		return (1);
	}
	return (0);
}

static int	check_duplicate_color(int *color_flag, char *type_name)
{
	if (*color_flag)
	{
		printf("❌ Duplicate color definition: %s\n", type_name);
		return (FALSE);
	}
	return (TRUE);
}

static char	*skip_to_color_values(char *line)
{
	int	i;

	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (NULL);
	return (&line[i]);
}

static int	validate_and_parse_rgb(char *rgb_start, t_color *target_color, 
								char *type_name)
{
	if (!rgb_start)
	{
		printf("❌ No color values found for %s\n", type_name);
		return (FALSE);
	}
	if (!parse_rgb_values(rgb_start, target_color))
	{
		printf("❌ Invalid RGB values for %s\n", type_name);
		return (FALSE);
	}
	return (TRUE);
}

int	parse_color_line(t_data *data, char *line)
{
	t_color	*target_color;
	char	*type_name;
	int		*color_flag;
	char	*rgb_start;

	if (!identify_color_type(line, &target_color, 
			&type_name, &color_flag, data))
		return (FALSE);
	if (!check_duplicate_color(color_flag, type_name))
		return (FALSE);
	rgb_start = skip_to_color_values(line);
	if (!validate_and_parse_rgb(rgb_start, target_color, type_name))
		return (FALSE);
	*color_flag = 1;
	printf("✅ %s color: RGB(%d, %d, %d)\n", 
		type_name, target_color->r, target_color->g, target_color->b);
	return (TRUE);
}
