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
            if (is_whitespace(str[*i]) || is_special_char(str[*i]))
                break;
        }
        
        (i)++;
    }

    int len = i - start;
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
        while (is_whitespace(input[i]))
            i++;
        
        if (!input[i])
            break;
        
        if (input[i] == '|')
        {
            new = new_token(type_Pipe, NULL);
            add_token(&tokens, new);
            i++;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            new = new_token(type_Redir_app, NULL);
            add_token(&tokens, new);
            i += 2;
        }    
        else if (input[i] == '>')
        {
            new = new_token(type_Redir_out, NULL);
            add_token(&tokens, new);
            i++;
        }
        else if (input[i] == '<')
        {
            new = new_token(type_Redir_in, NULL);
            add_token(&tokens, new);
            i++;
        }
        else
        {
            char *word = extract_word_with_quotes(input, i);
            new = new_token(type_Word, word);
            add_token(&tokens, new);
        }
    }
    
    return (tokens);
}