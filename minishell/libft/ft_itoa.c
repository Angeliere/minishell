/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:06:56 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/06 13:56:26 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*malloced(int n, int *len)
{
	char			*str;
	unsigned int	num;

	if (n <= 0)
	{
		(*len) = 1;
		num = (unsigned int)(-1 * (long)n);
	}
	else
	{
		(*len) = 0;
		num = (unsigned int)n;
	}
	while (num != 0)
	{
		(*len)++;
		num /= 10;
	}
	str = (char *)malloc(*len + 1);
	if (!str)
		return (NULL);
	str[*len] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int				length;
	unsigned int	num;
	char			*str;

	str = malloced (n, &length);
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		num = (unsigned int)(-1 * (long)n);
	else
		num = ((unsigned int)n);
	while (num > 0)
	{
		str[--length] = '0' + (num % 10);
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
/*
#include <limits.h> 
int main() {
    int numbers[] = {123, -456, 0, INT_MIN, INT_MAX};
    char *s = ft_itoa(numbers[4]);
    printf("itoa(%d) = '%s'\n", numbers[4], s);
    return 0;
}*/
