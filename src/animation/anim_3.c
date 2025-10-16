/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:27:35 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:27:37 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	get_current_time(void)
{
	return (mlx_get_time());
}

void	copy_base_path(char *frame_path, char *base_path, int *len)
{
	*len = ft_strlen(base_path);
	ft_strncpy(frame_path, base_path, *len);
}

void	add_frame_prefix(char *frame_path, int len)
{
	frame_path[len] = '/';
	frame_path[len + 1] = 'f';
	frame_path[len + 2] = 'r';
	frame_path[len + 3] = 'a';
	frame_path[len + 4] = 'm';
	frame_path[len + 5] = 'e';
	frame_path[len + 6] = '_';
}

void	add_frame_number(char *frame_path, int len, int frame_num)
{
	if (frame_num < 10)
	{
		frame_path[len + 7] = '0' + frame_num;
		frame_path[len + 8] = '.';
		frame_path[len + 9] = 'p';
		frame_path[len + 10] = 'n';
		frame_path[len + 11] = 'g';
		frame_path[len + 12] = '\0';
	}
	else
	{
		frame_path[len + 7] = '0' + (frame_num / 10);
		frame_path[len + 8] = '0' + (frame_num % 10);
		frame_path[len + 9] = '.';
		frame_path[len + 10] = 'p';
		frame_path[len + 11] = 'n';
		frame_path[len + 12] = 'g';
		frame_path[len + 13] = '\0';
	}
}
