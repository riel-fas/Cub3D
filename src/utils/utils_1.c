/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 03:37:37 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 02:21:00 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Counts the number of words separated by a specific delimiter
int	count_words_internal(char *str, char delimiter)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
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

// Checks if a character is a whitespace character
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

// Finds the first occurrence of character c in string str
char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}

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
