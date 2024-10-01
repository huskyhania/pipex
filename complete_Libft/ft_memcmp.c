/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:26:27 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/02 12:46:00 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cast_s1;
	unsigned char	*cast_s2;

	i = 0;
	cast_s1 = (unsigned char *) s1;
	cast_s2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while ((i < n) && (cast_s1[i] == cast_s2[i]))
		i++;
	if (i == n)
		return (0);
	return (cast_s1[i] - cast_s2[i]);
}
