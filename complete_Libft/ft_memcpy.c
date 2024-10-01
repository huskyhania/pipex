/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:32:00 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/06 19:18:00 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*cast_dest;
	char	*cast_src;

	i = 0;
	cast_dest = (char *) dst;
	cast_src = (char *) src;
	while (i < n && (dst != NULL || src != NULL))
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return (dst);
}
