/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:57 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/04/28 15:42:18 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	test;

	test = 0;
	if (n == 0)
		return (0);
	while (test < n - 1 && s1[test] == s2[test]
		&& (s1[test] != '\0' || s2[test] != '\0'))
		test++;
	if (test == n)
		return (0);
	return ((unsigned char)(s1[test]) - (unsigned char)(s2[test]));
}
