/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 20:50:59 by aschweit         ###   ########.fr       */
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
    struct termios term;
    tcgetattr(STDIN_FILENO, &g_original_term);
	term = g_original_term; 
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &g_original_term);
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
		line_input = read_until_closed_quotes(line_input);
		end = handle_input(line_input, shell);
	}
	free_envp(shell->my_envp);
	free(shell);
	restore_terminal();
	rl_clear_history();
	return (0);
}
