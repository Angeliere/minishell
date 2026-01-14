/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 20:30:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_name_match(char *env_str, char *var_name, int len)
{
	if (ft_strncmp(env_str, var_name, len) == 0 && env_str[len] == '=')
		return (1);
	return (0);
}

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	int		len;

	if (!var_name || !envp)
		return (ft_strdup(""));
	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (var_name_match(envp[i], var_name, len))
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = envp;
	shell->my_envp = copy_envp(envp);
	if (!shell->my_envp)
	{
		free(shell);
		return (NULL);
	}
	shell->last_exit_status = 0;
	return (shell);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
