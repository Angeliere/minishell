/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:30:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 22:00:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*get_special_var(char c, t_shell *shell, int *i)
{
	(*i)++;
	if (c == '?')
		return (ft_itoa(shell->last_exit_status));
	if (c == '$')
		return (ft_itoa(getpid()));
	return (ft_strdup(""));
}

static char	*expand_one_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*value;

	(*i)++;
	if (!str[*i] || (str[*i] != '?' && str[*i] != '$'
			&& !is_var_char(str[*i])))
		return (ft_strdup("$"));
	if (str[*i] == '?' || str[*i] == '$')
		return (get_special_var(str[*i], shell, i));
	var_name = extract_var_name(str, i);
	if (!var_name || !*var_name)
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	value = get_env_value(var_name, shell->my_envp);
	free(var_name);
	return (value);
}

static char	*append_str(char *result, char *str, int start, int end)
{
	char	*tmp;
	char	*part;

	tmp = result;
	part = ft_substr(str, start, end - start);
	result = ft_strjoin(tmp, part);
	free(tmp);
	free(part);
	return (result);
}

char	*expand_word_with_vars(char *str, t_shell *shell)
{
	char	*result;
	char	*tmp;
	char	*var_val;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		if (i > start)
			result = append_str(result, str, start, i);
		if (str[i] == '$')
		{
			var_val = expand_one_var(str, &i, shell);
			tmp = result;
			result = ft_strjoin(tmp, var_val);
			free(tmp);
			free(var_val);
		}
	}
	return (result);
}
