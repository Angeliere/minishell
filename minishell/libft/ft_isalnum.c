/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:40 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/05 18:53:16 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if (!(c != '\0' && ((c >= 'a' && c <= 'z')
				|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))))
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
    c = '[';
    printf("%d\n", ft_isalnum(c));
    return (0);
}
*/
