/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 22:17:11 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quotes(char *s)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*s)
	{
		if (*s == '\'' && !in_double)
			in_single = !in_single;
		else if (*s == '"' && !in_single)
			in_double = !in_double;
		s++;
	}
	return (in_single || in_double);
}

char	*read_until_closed_quotes(char *line)
{
	char	*tmp;
	char	*next;

	if (!line)
		return (NULL);
	while (has_unclosed_quotes(line))
	{
		next = readline("> ");
		if (!next)
			return (line);
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = line;
		line = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
	}
	return (line);
}

void	process_line(char *line_input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(line_input);
	tokens = tokenize_with_quotes(line_input);
	cmds = parse(tokens, shell);
	if (cmds)
		shell->last_exit_status = execute_cmds(cmds, shell);
	free_tokens(tokens);
	free_commands(cmds);
}

void	clean_main(t_shell *shell)
{
	free_envp(shell->my_envp);
	free(shell);
	restore_terminal();
	rl_clear_history();
	return ;
}
