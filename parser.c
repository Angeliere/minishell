/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 22:17:48 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_partial_argv(char **argv, int count)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (i < count)
		free(argv[i++]);
	free(argv);
}

char	**build_argv(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_argv_ctx	ctx;

	ctx.argv = alloc_argv(*tokens, &ctx.i);
	if (!ctx.argv)
		return (NULL);
	ctx.current = *tokens;
	ctx.cmd = cmd;
	ctx.shell = shell;
	if (!fill_argv(&ctx))
		return (NULL);
	ctx.argv[ctx.i] = NULL;
	*tokens = ctx.current;
	return (ctx.argv);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_token	*tok;
	t_cmd	*cmd;

	if (!check_syntax(tokens))
		return (NULL);
	head = NULL;
	tok = tokens;
	while (tok)
	{
		cmd = new_cmd();
		if (!cmd)
			return (free_commands(head), NULL);
		cmd->argv = build_argv(&tok, cmd, shell);
		if (!cmd->argv)
			return (free(cmd), free_commands(head), NULL);
		add_cmd(&head, cmd);
		if (tok && tok->type == type_Pipe)
			tok = tok->next;
	}
	return (head);
}
