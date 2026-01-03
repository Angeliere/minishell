/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:48 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/07 14:24:49 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int c)
{
	if (!(c >= 0 && c <= 127))
	{
		return (0);
	}
	else
	{
		return (1);
	}
}
/*
#include <stdio.h>

int main()
{
    char c;
    c = '0';
    printf("%d\n", ft_isascii(c));
    return (0);
}
*/
