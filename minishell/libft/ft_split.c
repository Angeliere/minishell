/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:09:18 by aschweit          #+#    #+#             */
/*   Updated: 2025/05/09 12:31:15 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
	{
		return (NULL);
	}
	if (word)
	{
		while (i < len)
		{
			word[i] = s[i];
			i++;
		}
		word[len] = '\0';
	}
	return (word);
}

static void	free_split(char **split_result, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
}

static const char	*s_deli_word(const char **s, char c, char **result, int *i)
{
	while (**s && **s == c)
		(*s)++;
	if (**s)
	{
		result[*i] = get_word(*s, c);
		if (!result[*i])
		{
			return (NULL);
		}
		(*i)++;
		while (**s && **s != c)
			(*s)++;
	}
	return (*s);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		s = s_deli_word(&s, c, result, &i);
		if (!s)
		{
			free_split(result, i);
			return (NULL);
		}
	}
	result[i] = NULL;
	return (result);
}

/*
#include <stdio.h>
int	main(void)
{
	char	**result;
	int		i;
	char	*str = "try again , this time";
	char	delimiter = ',';

	result = ft_split(str, delimiter);
	i = 0;
	while (result[i])
	{
		printf("Word %d: %s\n", i, result[i]);
		free(result[i]); 
		i++;
	}
	free(result); 

	return (0);
}*/
