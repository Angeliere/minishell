/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                     :+:      :+:    :+:      */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2025/10/08 12:32:07 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/*void setup_terminal(void)
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;  
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}*/

/*int environment_variables(char const * envp)
{
    char *value;

    value = getenv(envp);
    if(value)
        printf("%s = %s\n", envp , value);
    else
        return (0);
    return(1);
}
void launch_executable(const char * path, char const ** args, char const ** envp)
{
    execve(path, args, envp);
}*/
void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(void)
{
    t_token *tokens;
    char *line_input;
    int end = 0;
    signal(SIGINT, handle_sigint);
    while(!end)
    {
        line_input = readline("minishell> ");
        if(!line_input /*|| exit_line(line_input)*/)
        {
            printf("exit\n");
            break;
        }
        if(!*line_input)
        { 
            free(line_input);
            continue;
        }
        if((strcmp(line_input , "exit") == 0))
        {
            free(line_input);
            break;
        }
        add_history(line_input);
        tokens = tokenize_with_quotes(line_input);
        print_tokens(tokens);
        /*execute_command(line_input);*/
        print_tokens(tokens);
        free_tokens(tokens);
        free(line_input);
    }
    rl_clear_history();
	return (0);
}