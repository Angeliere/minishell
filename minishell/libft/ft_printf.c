/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:35:43 by aschweit          #+#    #+#             */
/*   Updated: 2025/09/17 13:58:52 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	check_specifier(va_list args, char specifier)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (specifier == 'u')
		return (ft_putnbr_unsigned(va_arg(args, int), 1));
	if (specifier == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 1));
	if (specifier == 'X')
		return (ft_putnbr_hex_caps(va_arg(args, unsigned int), 1));
	if (specifier == 'p')
		return (ft_putnbr_hex_ptr(va_arg(args, void *), 1));
	if (specifier == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_vprintf(const char *format, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (-1);
			i++;
			count += check_specifier(args, format[i]);
		}
		else
			count += ft_putchar_fd(format[i], 1);
		i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (0);
	va_start(args, format);
	count = ft_vprintf(format, args);
	va_end(args);
	return (count);
}
/*
#include <stdio.h>
#include <limits.h>
int main()
{
	printf("%c", '0');
	printf(" %c ", '0');
	printf(" %c", '0' - 256);
	printf("%c ", '0' + 256);
	printf(" %c %c %c ", '0', 0, '1');
	printf(" %c %c %c ", ' ', ' ', ' ');
	printf(" %c %c %c ", '1', '2', '3');
	printf(" %c %c %c ", '2', '1', 0);
	printf(" %c %c %c \n", 0, '1', '2');
	ft_printf("%c", '0');
	ft_printf(" %c ", '0');
	ft_printf(" %c", '0' - 256);
	ft_printf("%c ", '0' + 256);
	ft_printf(" %c %c %c ", '0', 0, '1');
	ft_printf(" %c %c %c ", ' ', ' ', ' ');
	ft_printf(" %c %c %c ", '1', '2', '3');
	ft_printf(" %c %c %c ", '2', '1', 0);
	ft_printf(" %c %c %c\n\n ", 0, '1', '2');

	printf(" %d ", 0);
	printf(" %d ", -1);
	printf(" %d ", 1);
	printf(" %d ", 9);
	printf(" %d ", 10);
	printf(" %d ", 11);
	printf(" %d ", 15);
	printf(" %d ", 16);
	printf(" %d ", 17);
	printf(" %d ", 99);
	printf(" %d ", 100);
	printf(" %d ", 101);
	printf(" %d ", -9);
	printf(" %d ", -10);
	printf(" %d ", -11);
	printf(" %d ", -14);
	printf(" %d ", -15);
	printf(" %d ", -16);
	printf(" %d ", -99);
	printf(" %d ", -100);
	printf(" %d ", -101);
	printf(" %d ", INT_MAX);
	printf(" %d ", INT_MIN);
	printf(" %d ", 92247);
	printf(" %d %d %d %d\n", INT_MAX, INT_MIN, 0, -42);

	ft_printf(" %d ", 0);
    ft_printf(" %d ", -1);
    ft_printf(" %d ", 1);
    ft_printf(" %d ", 9);
    ft_printf(" %d ", 10);
    ft_printf(" %d ", 11);
    ft_printf(" %d ", 15);
    ft_printf(" %d ", 16);
    ft_printf(" %d ", 17);
    ft_printf(" %d ", 99);
    ft_printf(" %d ", 100);
    ft_printf(" %d ", 101);
    ft_printf(" %d ", -9);
    ft_printf(" %d ", -10);
    ft_printf(" %d ", -11);
    ft_printf(" %d ", -14);
    ft_printf(" %d ", -15);
    ft_printf(" %d ", -16);
    ft_printf(" %d ", -99);
    ft_printf(" %d ", -100);
    ft_printf(" %d ", -101);
    ft_printf(" %d ", INT_MAX);
    ft_printf(" %d ", INT_MIN);
    ft_printf(" %d ", 92247);
    ft_printf(" %d %d %d %d", INT_MAX, INT_MIN, 0, -42);
}*/
