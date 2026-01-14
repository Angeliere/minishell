/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 20:00:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;

	if (!argv[1])
	{
		print_export(shell->my_envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			shell->my_envp = set_env_var(shell->my_envp, argv[i]);
		i++;
	}
	return (0);
}
