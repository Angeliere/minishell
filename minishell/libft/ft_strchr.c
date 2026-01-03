/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:19 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/09 12:40:48 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (c == '\0' || c == 1024)
	{
		while (str[i] != '\0')
			i++;
		return ((char *)&str[i]);
	}
	while (str[i] != '\0')
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <unistd.h>
#include <stdio.h>

int main()
{
        char test[20] = "this zill not stand";
        printf("%s\n", ft_strchr(test,'o') );

}*/
