/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:54 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/05 19:00:04 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int c)
{
	if (c != '\0' && (c >= 'A' && c <= 'Z'))
		c += 32;
	return (c);
}
/*
#include <stdio.h>
int main()
{
    char c;
    c = 'A';
    printf("%c\n", ft_tolower(c));
    return (0);
}
*/
