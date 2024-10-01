/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:14:30 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/05 17:39:19 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	finish;
	size_t	index;
	char	*trimmed;

	start = 0;
	finish = ft_strlen(s1);
	if (!s1)
		return (0);
	while (s1[start] && in_set(s1[start], set))
		start++;
	while (finish > start && in_set(s1[finish - 1], set))
		finish--;
	trimmed = malloc((finish - start + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	index = 0;
	while (start < finish)
		trimmed[index++] = s1[start++];
	trimmed[index] = '\0';
	return (trimmed);
}
