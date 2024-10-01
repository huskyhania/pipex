/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:37:07 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/06 19:33:11 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*cast_str;

	i = 0;
	cast_str = (const unsigned char *) s;
	while (i < n)
	{
		if (cast_str[i] == (unsigned char)c)
			return ((void *) &cast_str[i]);
		i++;
	}
	return (NULL);
}
