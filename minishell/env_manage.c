/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 20:45:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**copy_envp(char **envp)
{
	char	**new_env;
	int		i;
	int		count;

	count = count_env(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	find_env_index(char **envp, char *var_name)
{
	int		i;
	int		len;

	if (!var_name || !envp)
		return (-1);
	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**update_existing_var(char **envp, int idx, char *var_assign)
{
	free(envp[idx]);
	envp[idx] = ft_strdup(var_assign);
	return (envp);
}

static char	**add_new_var(char **envp, char *var_assign)
{
	char	**new_env;
	int		i;
	int		count;

	count = count_env(envp);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (envp);
	i = 0;
	while (envp[i])
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = ft_strdup(var_assign);
	new_env[i + 1] = NULL;
	free(envp);
	return (new_env);
}

char	**set_env_var(char **envp, char *var_assign)
{
	char	*eq_pos;
	char	*var_name;
	int		idx;

	eq_pos = ft_strchr(var_assign, '=');
	if (!eq_pos)
		return (envp);
	var_name = ft_substr(var_assign, 0, eq_pos - var_assign);
	if (!var_name)
		return (envp);
	idx = find_env_index(envp, var_name);
	free(var_name);
	if (idx >= 0)
		return (update_existing_var(envp, idx, var_assign));
	else
		return (add_new_var(envp, var_assign));
}

char	**unset_env_var(char **envp, char *var_name)
{
	char	**new_env;
	int		idx;
	int		i;
	int		j;

	idx = find_env_index(envp, var_name);
	if (idx < 0)
		return (envp);
	new_env = malloc(sizeof(char *) * count_env(envp));
	if (!new_env)
		return (envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != idx)
			new_env[j++] = envp[i];
		else
			free(envp[i]);
		i++;
	}
	new_env[j] = NULL;
	free(envp);
	return (new_env);
}
