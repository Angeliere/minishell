/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_str_manip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 22:43:31 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char** dup_arr(const char *s, char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == ':')
			count++;
		i++;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	return (arr);
}

char	*substr_dup(const char *s, int start, int len)
{
	char	*str;
	int		i;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

int	has_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*search_paths(char *cmd, char **paths)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = ft_strjoin3(paths[i], "/", cmd);
		if (full && access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin3(const char *a, const char *b, const char *c)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(a, b);
	if (!s1)
		return (NULL);
	s2 = ft_strjoin(s1, c);
	free(s1);
	return (s2);
}
