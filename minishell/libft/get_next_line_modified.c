/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:25:35 by aschweit          #+#    #+#             */
/*   Updated: 2025/09/23 14:26:45 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	find_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_line(char *s)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = s[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*trim_stash(char *stash)
{
	int		i;
	char	*ret;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	ret = ft_strdup(stash + i + 1);
	free(stash);
	return (ret);
}

char	*return_line_and_trim(char **stash)
{
	char	*line;

	if (!*stash || (*stash)[0] == '\0')
	{
		free(*stash);
		*stash = (NULL);
		return (NULL);
	}
	line = extract_line(*stash);
	*stash = trim_stash(*stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			buffer[BUFFER_SIZE + 1];
	int				byte_read;
	char			*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	byte_read = 1;
	if (!stash)
		stash = ft_strdup("");
	while (byte_read > 0 && find_newline(stash) == -1)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[byte_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	return (return_line_and_trim(&stash));
}
/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
    int fd1 = open("text.txt", O_RDONLY);
    char *line;
    while((line = get_next_line(fd1)) != NULL)
    {
        printf("line : %s",line);
        free(line);
    }
    close(fd1);
    return(0);
}*/
