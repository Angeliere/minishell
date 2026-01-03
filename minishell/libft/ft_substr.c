/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:52 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/07 14:50:30 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*result;

	if (s == NULL || start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	str_len = ft_strlen(s);
	if (start + len > str_len)
		len = str_len - start;
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy (result, s + start, len);
	result[len] = '\0';
	return (result);
}
/*
int main() {
    const char* original_str = "Hello, World!";
    int start = 3;
    int length = 5;

    char* sub = ft_substr(original_str, start, length);
    if (sub != NULL) {
        printf("Substring: %s\n", sub);
        free(sub); 
    } else {
        printf("Error extracting substring.\n");
    }

    return 0;
}*/
