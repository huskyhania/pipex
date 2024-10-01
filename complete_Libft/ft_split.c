/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:14:15 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/08 18:09:18 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static size_t	word_length(const char *s, int start, char c)
{
	size_t	length;

	length = 0;
	while (s[start + length] && s[start + length] != c)
		length++;
	return (length);
}

static void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

static char	**helper_split(char const *s, char c, char **split_list, int ar)
{
	int		start;
	size_t	len;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			len = word_length(s, start, c);
			split_list[ar] = ft_substr(s, start, len);
			if (!split_list[ar])
			{
				free_2d(split_list);
				return (NULL);
			}
			ar++;
			i += len;
		}
		else
			i++;
	}
	split_list[ar] = (NULL);
	return (split_list);
}

char	**ft_split(char const *s, char c)
{
	int		k;
	char	**split_list;
	char	**result;
	int		arr_index;

	k = count_words(s, c);
	arr_index = 0;
	split_list = malloc(sizeof(char *) * (k + 1));
	if (!split_list)
		return (NULL);
	result = helper_split(s, c, split_list, arr_index);
	return (result);
}
