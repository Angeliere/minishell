/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 20:30:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_exit_status(int status)
{
	return (ft_itoa(status));
}

static char	*expand_pid(void)
{
	return (ft_itoa(getpid()));
}

static char	*expand_normal_var(char *var_name, char **envp)
{
	return (get_env_value(var_name, envp));
}

char	*expand_var(t_token *token, t_shell *shell)
{
	if (!token || !shell)
		return (NULL);
	if (token->in_single_quotes)
		return (ft_strdup(token->value));
	if (token->type == type_Var_exit)
		return (expand_exit_status(shell->last_exit_status));
	else if (token->type == type_Var_pid)
		return (expand_pid());
	else if (token->type == type_Var)
		return (expand_normal_var(token->value, shell->my_envp));
	return (NULL);
}
