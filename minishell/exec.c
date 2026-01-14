/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:02:40 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/13 22:50:36 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

static char	*ft_strjoin3(const char *a, const char *b, const char *c)
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

static void	free_split(char **arr)
{
	int i = 0;
	if (!arr) return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	**split_colon(const char *s)
{
	int count = 1;
	int i = 0, j = 0, start = 0;
	char **arr;

	if (!s)
		return (NULL);
	while (s[i])
		if (s[i++] == ':')
			count++;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (1)
	{
		if (s[i] == ':' || s[i] == '\0')
		{
			int len = i - start;
			arr[j] = malloc(len + 1);
			if (!arr[j])
				return (NULL); /* (simple v0: not handling partial free) */
			for (int k = 0; k < len; k++)
				arr[j][k] = s[start + k];
			arr[j][len] = '\0';
			j++;
			if (s[i] == '\0')
				break;
			start = i + 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static int	exec_builtin(char **argv, t_shell *shell)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd(argv));
	if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, shell));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, shell));
	if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(argv, shell->my_envp));
	if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	return (1);
}

static void	setup_pipe(int prev_fd, int pipefd[2], int has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static char	*resolve_path(char *cmd, char **envp)
{
	char *path_env;
	char **paths;
	char *full;
	int i;

	if (!cmd || !*cmd)
		return (NULL);
	/* if contains '/', try direct */
	for (i = 0; cmd[i]; i++) // replace it with a while loop.
		if (cmd[i] == '/')
			return (strdup(cmd));
	(void)envp;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = split_colon(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin3(paths[i], "/", cmd);
		if (full && access(full, X_OK) == 0)
		{
			free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static void	exec_child(t_cmd *cmd, t_shell *sh)
{
	char	*path;

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

static int	update_prev_fd(int prev_fd, int pipefd[2], int has_next)
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
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (!cmds || !cmds->argv)
		return (0);
	if (!cmds->next && is_builtin(cmds->argv[0]))
		return (exec_builtin(cmds->argv, sh));
	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == 0)
		{
			setup_pipe(prev_fd, pipefd, cmds->next != NULL);
			exec_child(cmds, sh);
		}
		prev_fd = update_prev_fd(prev_fd, pipefd, cmds->next != NULL);
		cmds = cmds->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
