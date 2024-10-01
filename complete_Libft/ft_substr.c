/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:48:16 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/05 17:54:20 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr_str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return ((char *)ft_calloc(1, 1));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	substr_str = malloc((len + 1) * sizeof(char));
	if (!substr_str)
		return (NULL);
	while (i < len)
	{
		substr_str[i] = s[start];
		i++;
		start++;
	}
	substr_str[i] = '\0';
	return (substr_str);
}
