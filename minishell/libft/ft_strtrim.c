/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:07:49 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/07 16:03:39 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	isstr(const char *trim_char, char c)
{
	while (*trim_char != '\0')
	{
		if (*trim_char == c)
			return (1);
		trim_char++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (s1[start] != '\0' && isstr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && isstr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	result = (char *)malloc((end - start + 1) + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy (result, s1 + start, (end - start + 1));
	result[(end - start + 1)] = '\0';
	return (result);
}
/*
int main() {
    const char* original_str = "///Hello, World!///";
    const char* trim_chars = "/!";  // Characters to trim

    char* trimmed_str = ft_strtrim(original_str, trim_chars);

    if (trimmed_str != NULL) {
        printf("Trimmed string: '%s'\n", trimmed_str);
        free(trimmed_str);  // Free the allocated memory
    } 
    else {
        printf("Error trimming string.\n");
    }

    return 0;
}*/
