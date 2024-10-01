/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:30:22 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/06 19:23:54 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*cast_dest;
	const char	*cast_src;

	cast_dest = (char *) dst;
	cast_src = (char *) src;
	if (cast_dest == cast_src)
		return (dst);
	if (cast_dest > cast_src && cast_dest < cast_src + len)
	{
		i = len;
		while (i > 0)
		{
			cast_dest[i - 1] = cast_src[i -1];
			i--;
		}
	}
	else
	{
		while (len--)
			*cast_dest++ = *cast_src++;
	}
	return (dst);
}
