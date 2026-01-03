/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:58 by aschweit          #+#    #+#             */
/*   Updated: 2025/09/17 13:56:50 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	printf_hex_recursive(uintptr_t addr, int fd)
{
	char	*hex;
	int		count;

	count = 0;
	hex = "0123456789abcdef";
	if (addr >= 16)
		count += printf_hex_recursive(addr / 16, fd);
	count += ft_putchar_fd(hex[addr % 16], fd);
	return (count);
}

int	ft_putnbr_hex_ptr(void *n, int fd)
{
	uintptr_t	addr;
	int			count;

	count = 0;
	addr = (uintptr_t)n;
	if (n == 0)
	{
		write (fd, "(nil)", 5);
		return (5);
	}
	count += write(fd, "0x", 2);
	count += printf_hex_recursive(addr, fd);
	return (count);
}
