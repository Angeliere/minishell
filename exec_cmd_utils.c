/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 22:34:19 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	exec_single_builtin(t_cmd *cmds, t_shell *sh)
{
	if (!cmds || !cmds->argv)
		return (0);
	if (!cmds->next && is_builtin(cmds->argv[0]) && !cmds->redirs)
		return (exec_builtin(cmds->argv, sh));
	return (-1);
}
int	fork_loop(t_cmd *cmds, t_shell *sh)
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

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
	return (0);
}
int	wait_children(void)
{
	int	status;

	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}