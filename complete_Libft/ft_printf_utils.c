/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:30:52 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/07/25 19:55:47 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	int	char_count;

	char_count = write(1, &c, 1);
	return (char_count);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		i = i + 6;
		return (i);
	}
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putnbr_recursive(long n, int base, char is_upper, int result)
{
	char	*base_chars;
	char	*cap_base_chars;

	base_chars = "0123456789abcdef";
	cap_base_chars = "0123456789ABCDEF";
	if (n < base)
	{
		if (is_upper != 'X')
			result = ft_putchar(base_chars[n]);
		else
			result = ft_putchar(cap_base_chars[n]);
		if (result == -1)
			return (-1);
		return (result);
	}
	else
	{
		result = ft_putnbr_recursive(n / base, base, is_upper, result);
		if (result == -1)
			return (-1);
		result += ft_putnbr_recursive(n % base, base, is_upper, result);
		if (result == -1)
			return (-1);
		return (result);
	}
}

int	ft_putnbr(long n, int base, char is_upper)
{
	int	result;
	int	counter;

	result = 0;
	counter = 0;
	if (n < 0)
	{
		result = write(1, "-", 1);
		if (result == -1)
			return (-1);
		result = ft_putnbr_recursive(-n, base, is_upper, counter);
		if (result == -1)
			return (-1);
		return (result + 1);
	}
	else
		return (ft_putnbr_recursive(n, base, is_upper, counter));
}

int	ft_pointer(void *ptr, int i, int length, char *base_chars)
{
	uintptr_t	helper;
	char		string[17];

	helper = (uintptr_t)ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	if (helper == 0)
	{
		if (ft_putchar('0') == -1)
			return (-1);
		return (3);
	}
	while (helper != 0)
	{
		string[i++] = base_chars[helper % 16];
		helper = helper / 16;
	}
	while (i--)
	{
		if (ft_putchar(string[i]) == -1)
			return (-1);
		length++;
	}
	return (length + 2);
}
