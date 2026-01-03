/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:12:52 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/05 19:18:36 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
void to_upper_with_index(unsigned int i, char *c)
{
    int d;
    while(c[d] != '\0')
    {
        if (i % 2 == 0 && c[d] >= 'a' && c[d] <= 'z')
            c[d] = c[d] - 32;
        d++;
    }
}

int main(void)
{
    char str[] = "hello world";
    ft_striteri(str, to_upper_with_index);
    printf("%s\n", str);
    return 0;
}
*/
