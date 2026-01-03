/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:25 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/07 14:26:26 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (dest[c] != '\0' && c < size)
		c++;
	if (c == size)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && (c + i) < (size - 1))
	{
		dest[c + i] = src[i];
		i++;
	}
	dest [i + c] = '\0';
	return (c + ft_strlen(src));
}
/*
int main()
{
        char test1[10] = "inning";
        char test[10] = "beg";
        printf("%ld\n" , ft_strlcat(test ,test1, 1));
        printf ("%s", test);
        return (0);
}
*/
