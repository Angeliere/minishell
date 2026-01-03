/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:21 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/07 14:53:09 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h" 

char	*ft_strdup(const char *s)
{
	char	*copied;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	copied = malloc(len + 1);
	if (copied == NULL)
		return (NULL);
	while (s[i])
	{
		copied[i] = s[i];
		i++;
	}
	copied[i] = '\0';
	return (copied);
}
/*
#include <unistd.h>
#include <stdio.h>
int main()
{
    char try[15] = "a";
    char* duplicated = ft_strdup(try);
    printf("%s\n",duplicated);
    free(duplicated);
}*/
