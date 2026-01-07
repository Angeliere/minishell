/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                     :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2025/10/08 12:32:07 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *new_token(t_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

void add_token(t_token **head, t_token *new)
{
    t_token *current;

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

char *extract_word_with_quotes(char *str, int *i)
{
    int start;
    char *word;
    int j;
    t_quote state;

    state.in_single = 0;
    state.in_double = 0;
    start = *i;

    while (str[*i])
    {
        if (str[*i] == '\'' && !state.in_double)
            state.in_single = !state.in_single;
        else if (str[*i] == '"' && !state.in_single)
            state.in_double = !state.in_double;
        
        if (!state.in_single && !state.in_double)
        {
            if (is_space(str[*i]) || is_token_char(str[*i]))
                break;
        }

        (*i)++;
    }

    int len = *i - start;
    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    
    j = 0;
    while (j < len)
    {
        word[j] = str[start + j];
        j++;
    }
    word[j] = '\0';
    
    return (word);
}

t_token *tokenize_with_quotes(char *input)
{
    t_token *tokens;
    t_token *new;
    int i;

    tokens = NULL;
    i = 0;
    
    while (input[i])
    {
        while (is_space(input[i]))
            i++;
        
        if (!input[i])
            break;
        
        if (input[i] == '|')
        {
            new = new_token(type_Pipe, NULL);
            printf("pipe + 1\n");
            add_token(&tokens, new);
            i++;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            new = new_token(type_Redir_app, NULL);
            printf("redirection\n");
            add_token(&tokens, new);
            i += 2;
        }    
        else if (input[i] == '>')
        {
            new = new_token(type_Redir_out, NULL);
            printf("in\n");
            add_token(&tokens, new);
            i++;
        }
        else if (input[i] == '<')
        {
            new = new_token(type_Redir_in, NULL);
            printf("out\n");
            add_token(&tokens, new);
            i++;
        }
        else
        {
            char *word = extract_word_with_quotes(input, &i);
            new = new_token(type_Word, word);
            printf("quotes\n");
            add_token(&tokens, new);
        }
    }
    return (tokens);
}