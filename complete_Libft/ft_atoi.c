/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:20:20 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/09/07 22:09:38 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int				negation;
	long long int	prev;
	long long int	number;

	negation = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			negation *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		prev = number * 10 + *str++ - 48;
		if (prev / 10 != number && negation == -1)
			return (0);
		if (prev / 10 != number && negation == 1)
			return (-1);
		number = prev;
	}
	return (number * negation);
}
