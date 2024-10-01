/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:03:39 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/06 19:34:43 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *) haystack);
	if (len < 1)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		while (needle[j] != '\0' && haystack[i + j] == needle[j]
			&& (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return ((char *) &haystack[i]);
		j = 0;
		i++;
	}
	return (NULL);
}
