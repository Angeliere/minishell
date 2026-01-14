/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:02:40 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 22:39:06 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

static char	**split_colon(const char *s)
{
	char	**arr;
	int		i;
	int		j;
	int		start;

	arr = 0;
	dup_arr(s, arr);
	i = 0;
	j = 0;
	start = 0;
	while (1)
	{
		if (s[i] == ':' || s[i] == '\0')
		{
			arr[j++] = substr_dup(s, start, i - start);
			if (!arr[j - 1])
				return (NULL);
			if (s[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

static char	*resolve_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full;

	(void)envp;
	if (!cmd || !*cmd)
		return (NULL);
	if (has_slash(cmd))
		return (strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = split_colon(path_env);
	if (!paths)
		return (NULL);
	full = search_paths(cmd, paths);
	free_split(paths);
	return (full);
}

void	exec_child(t_cmd *cmd, t_shell *sh)
{
	char	*path;

	apply_redirs(cmd->redirs);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd->argv, sh));
	path = resolve_path(cmd->argv[0], sh->envp);
	if (!path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(path, cmd->argv, sh->envp);
	perror("execve");
	exit(126);
}

int	update_prev_fd(int prev_fd, int pipefd[2], int has_next)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (has_next)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}

int	execute_cmds(t_cmd *cmds, t_shell *sh)
{
	int	ret;

	ret = exec_single_builtin(cmds, sh);
	if (ret != -1)
		return (ret);
	if (fork_loop(cmds, sh))
		return (1);
	return (wait_children());
}
