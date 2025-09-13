/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:21:25 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/13 21:26:08 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_type(char *line)
{
	if (!line)
		return (-1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA);
	return (-1);
}

int	validate_texture_extension(char *path)
{
	int	len;

	if (!path)
		return (FALSE);
	len = ft_strlen(path);
	if (len < 4)
		return (FALSE);
	return (ft_strncmp(path + len - 4, ".png", 4) == 0 || 
			ft_strncmp(path + len - 4, ".PNG", 4) == 0);
}