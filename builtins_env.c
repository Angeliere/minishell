/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 19:42:53 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv, t_shell *shell)
{
	int	i;

	(void)argv;
	if (!shell)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		ft_putstr_fd(shell->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
