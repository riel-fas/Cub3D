/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	
	len = ft_strlen(str);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	
	return (dup);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2 || n == 0)
		return (0);
	
	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	
	if (i == n)
		return (0);
	
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strtrim(char *str)
{
	char	*trimmed;
	int		start;
	int		end;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	
	// Find start (skip leading whitespace)
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t' || 
						  str[start] == '\n' || str[start] == '\r'))
		start++;
	
	// Find end (skip trailing whitespace)
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t' || 
							str[end] == '\n' || str[end] == '\r'))
		end--;
	
	// Calculate length
	len = end - start + 1;
	if (len <= 0)
	{
		trimmed = malloc(1);
		if (trimmed)
			trimmed[0] = '\0';
		return (trimmed);
	}
	
	// Allocate and copy
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	
	i = 0;
	while (i < len)
	{
		trimmed[i] = str[start + i];
		i++;
	}
	trimmed[i] = '\0';
	
	return (trimmed);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	if (!str)
		return (0);
	
	result = 0;
	sign = 1;
	i = 0;
	
	// Skip whitespace
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	
	// Handle sign
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	
	// Convert digits
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return (result * sign);
}

static int	count_words_internal(char *str, char delimiter)
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

static char	*extract_word(char *str, int *index, char delimiter)
{
	int		start;
	int		len;
	char	*word;
	int		i;

	// Skip delimiters
	while (str[*index] && str[*index] == delimiter)
		(*index)++;
	
	if (!str[*index])
		return (NULL);
	
	start = *index;
	
	// Find word length
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

char	**ft_split(char *str, char delimiter)
{
	char	**result;
	int		word_count;
	int		index;
	int		i;

	if (!str)
		return (NULL);
	
	word_count = count_words_internal(str, delimiter);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	
	index = 0;
	i = 0;
	while (i < word_count)
	{
		result[i] = extract_word(str, &index, delimiter);
		if (!result[i])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	
	result[i] = NULL;
	return (result);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	if (!str)
		return (NULL);
	
	i = 0;
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

	if (!str)
		return (0);
	
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
