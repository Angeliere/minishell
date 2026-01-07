/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                     :+:      :+:    :+:      */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2025/10/08 12:32:07 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*#include "libft.h"*/

typedef enum token_type
{
    type_Word,
    type_Pipe,       // "|"
    type_Redir_in,     // "<"
    type_Redir_app,      // "<<"
    type_Redir_out,    // ">"
    type_Redir_deli     // ">>"

}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}   t_token;

typedef struct s_quote
{
    int in_single; 
    int in_double;  
}   t_quote;

typedef struct s_redir
{
    int             type;      // REDIR_IN, REDIR_OUT, REDIR_APPEND
    char            *file;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **argv;
    t_redir         *redirs;
    struct s_cmd    *next;
}   t_cmd;

t_token *tokenize_with_quotes(char *input);
int is_token_char(char c);
int is_space(char c);

#endif


