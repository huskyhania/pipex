/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:01:56 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/05 16:40:41 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_letters(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	my_to_string(char *result, int n, int number)
{
	result[number] = '\0';
	if (n == 0)
	{
		result[0] = '0';
		return ;
	}
	if (n == -2147483648)
	{
		result[0] = '-';
		result[number - 1] = '8';
		number -= 1;
		n = -(n / 10);
	}
	else if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (--number >= 0 && n != 0)
	{
		result[number] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		number;

	number = count_letters(n);
	result = (char *)malloc((number + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	my_to_string(result, n, number);
	return (result);
}
