/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:11:18 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/05 17:47:11 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*count;

	i = 0;
	count = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			count = ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char)c)
		count = ((char *) &s[i]);
	return (count);
}
