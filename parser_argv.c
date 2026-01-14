/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 21:43:02 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alloc_argv(t_token *tokens, int *i)
{
	char	**argv;
	int		count;

	count = count_args(tokens);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	*i = 0;
	return (argv);
}

int	fill_argv(t_argv_ctx *ctx)
{
	while (ctx->current && ctx->current->type != type_Pipe)
	{
		if (is_redir(ctx->current->type))
		{
			if (!process_redir(&ctx->current, ctx->cmd))
				return (free_partial_argv(ctx->argv, ctx->i), 0);
		}
		else
		{
			add_word(ctx->current, ctx->argv, &ctx->i, ctx->shell);
			ctx->current = ctx->current->next;
		}
	}
	return (1);
}
