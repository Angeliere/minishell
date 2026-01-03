/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:53 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/05 18:54:10 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	if (!(c != '\0' && ((c >= ' ' && c <= '~'))))
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
    c = 'a';
    printf("%d\n", ft_isprint(c));
    return (0);
}
*/
