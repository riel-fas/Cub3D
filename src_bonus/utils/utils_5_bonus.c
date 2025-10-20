/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:31:20 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/25 18:32:52 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	skip_whitespace(char *line, int *index)
{
	if (!line || !index)
		return (FALSE);
	while (line[*index] && ft_isspace(line[*index]))
		(*index)++;
	return (TRUE);
}

int	count_words(char *str, char delimiter)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != delimiter && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == delimiter)
			in_word = 0;
		i++;
	}
	return (count);
}

// Copies at most n characters from src to dest
char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
