/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:57 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/05 19:00:14 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c != '\0' && (c >= 'a' && c <= 'z'))
		c -= 32;
	return (c);
}
/*
#include <stdio.h>

int main()
{
    char c;
    c = 'a';
    printf("%c\n", ft_toupper(c));
    return (0);
}
*/
