/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 22:22:52 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	g_original_term;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &g_original_term);
	term = g_original_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	restore_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_original_term);
}

static int	handle_input(char *line_input, t_shell *shell)
{
	line_input = read_until_closed_quotes(line_input);
	if (!line_input)
	{
		free(line_input);
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
	t_shell	*shell;
	int		end;

	(void)argc;
	(void)argv;
	end = 0;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	setup_terminal();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (!end)
	{
		line_input = readline("minishell> ");
		if (!line_input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		end = handle_input(line_input, shell);
	}
	clean_main(shell);
	return (0);
}
