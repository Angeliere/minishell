/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:23 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/06 14:17:35 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	char	*result;	

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy (result, s1, len1);
	ft_memcpy (result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}
/*
#include <stdio.h>
int     main(void)
{
    char *strs = "hello ";
	char *dest = "world";
	char* together = ft_strjoin(strs , dest);

    printf("New string: %s\n",together);
    free(together);
}*/
