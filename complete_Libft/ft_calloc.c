/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:54:52 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/08 22:10:42 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated_space;
	size_t	i;

	i = 0;
	if (count && UINT_MAX / count < size)
		return (NULL);
	allocated_space = malloc(count * size);
	if (!allocated_space)
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)allocated_space)[i] = 0;
		i++;
	}
	return (allocated_space);
}
