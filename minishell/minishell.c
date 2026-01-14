/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 20:30:00 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	process_line(char *line_input, t_shell *shell)
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

static int	handle_input(char *line_input, t_shell *shell)
{
	if (!line_input)
	{
		printf("exit\n");
		return (1);
	}
	if (!*line_input)
	{
		free(line_input);
		return (0);
	}
	if (ft_strncmp(line_input, "exit", 4) == 0)
	{
		free(line_input);
		return (1);
	}
	process_line(line_input, shell);
	free(line_input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_input;
	int		end;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	end = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (!end)
	{
		line_input = readline("minishell> ");
		end = handle_input(line_input, shell);
	}
	free_envp(shell->my_envp);
	free(shell);
	rl_clear_history();
	return (0);
}
