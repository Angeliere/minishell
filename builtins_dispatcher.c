/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:17:28 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 22:17:29 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (1);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, shell));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, shell));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv, shell));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	return (1);
}
