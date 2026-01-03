/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:59 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/07 14:39:14 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)ch)
			return (&((unsigned char *)str)[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main()
{
        char test[20] = "thas zill not stand";
        int test1 = 'i';
        char *ret;
        ret = ft_memchr(test,test1, 19);
        printf("%s\n", ret );
}*/
