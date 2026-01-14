/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 01:22:35 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 17:45:00 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(t_redir **head, t_redir *new)
{
	t_redir	*current;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_word(t_token *curr, char **argv, int *i, t_shell *shell)
{
	char	*cleaned;

	if (curr->type == type_Word)
	{
		cleaned = remove_quotes(curr->value);
		if (curr->in_double_quotes && ft_strchr(cleaned, '$'))
		{
			argv[(*i)++] = expand_word_with_vars(cleaned, shell);
			free(cleaned);
		}
		else
			argv[(*i)++] = cleaned;
	}
	else if (curr->type == type_Var || curr->type == type_Var_exit
		|| curr->type == type_Var_pid)
		argv[(*i)++] = expand_var(curr, shell);
}

void	add_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*current;

	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
