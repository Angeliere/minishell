/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:44 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/09 13:02:46 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	leng;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	leng = ft_strlen((char *)little);
	while (i + leng <= len && big[i] != '\0')
	{
		c = 0;
		while (little[c] != '\0' && big[i + c] == little[c])
			c++;
		if (leng == c)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <unistd.h>


int main()
{
        char *res = ft_strnstr(((void*)0), "fake", 3);
	if (res)
        printf("Found: %s\n", res);
	return 0;
}*/
