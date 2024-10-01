/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:27:28 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/07/25 19:55:29 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_choice(char specifier, va_list arguments)
{
	int		count;
	char	*base_chars;

	count = 0;
	base_chars = "0123456789abcdef";
	if (specifier == 'c')
		count = ft_putchar(va_arg(arguments, int));
	else if (specifier == 's')
		count = ft_putstr(va_arg(arguments, char *));
	else if (specifier == 'd' || specifier == 'i')
		count = ft_putnbr(va_arg(arguments, int), 10, specifier);
	else if (specifier == 'u')
		count = ft_putnbr(va_arg(arguments, unsigned int), 10, specifier);
	else if (specifier == 'x' || specifier == 'X')
		count = ft_putnbr(va_arg(arguments, unsigned int), 16, specifier);
	else if (specifier == 'p')
		count = ft_pointer(va_arg(arguments, void *), 0, 0, base_chars);
	else
		count = ft_putchar(specifier);
	return (count);
}

static int	helper(const char *s, va_list arguments, int count, int total)
{
	while (*s != '\0')
	{
		if (*s != '%')
		{
			if (write(1, s, 1) == -1)
				return (-1);
			total++;
		}
		if (*s == '%')
		{
			s++;
			if (*s == '\0')
				break ;
			else
			{
				count = print_choice(*s, arguments);
				if (count == -1)
					return (-1);
				total = total + count;
			}
		}
		s++;
	}
	return (total);
}

int	ft_printf(const char *s, ...)
{
	va_list	arguments;
	int		count;
	int		total_count;

	count = 0;
	total_count = 0;
	va_start(arguments, s);
	total_count = helper(s, arguments, count, total_count);
	va_end(arguments);
	return (total_count);
}
