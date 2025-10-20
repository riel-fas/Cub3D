/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 04:07:02 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/14 02:21:00 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Extracts a single word from string starting at index position
static char	*extract_word(char *str, int *index, char delimiter)
{
	int		start;
	int		len;
	char	*word;
	int		i;

	while (str[*index] && str[*index] == delimiter)
		(*index)++;
	if (!str[*index])
		return (NULL);
	start = *index;
	while (str[*index] && str[*index] != delimiter)
		(*index)++;
	len = *index - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// Frees partially allocated split result array in case of error
static void	free_split_result(char **result, int up_to_index)
{
	while (--up_to_index >= 0)
		free(result[up_to_index]);
	free(result);
}

// Allocates memory for the split result array
static char	**allocate_split_array(int word_count)
{
	char	**result;

	result = malloc(sizeof(char *) * (word_count + 1));
	return (result);
}

// Fills the split array with extracted words from the string
static char	**fill_split_array(char *str, char delimiter, int word_count)
{
	char	**result;
	int		index;
	int		i;

	result = allocate_split_array(word_count);
	if (!result)
		return (NULL);
	index = 0;
	i = 0;
	while (i < word_count)
	{
		result[i] = extract_word(str, &index, delimiter);
		if (!result[i])
		{
			free_split_result(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

// Splits a string into an array of words separated by delimiter
char	**ft_split(char *str, char delimiter)
{
	int	word_count;

	if (!str)
		return (NULL);
	word_count = count_words_internal(str, delimiter);
	return (fill_split_array(str, delimiter, word_count));
}
