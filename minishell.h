/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 22:44:12 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/* token types
	Pipe = "|"
	Redir_in = "<"
	Redir_app = "<<"
	Redir_out = ">"
	Redir_append = ">>"
	Var = "$"
*/
typedef enum token_type
{
	type_Word,
	type_Pipe,
	type_Redir_in,
	type_Redir_app,
	type_Redir_out,
	type_Redir_append,
	type_Var,
	type_Var_exit,
	type_Var_pid
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					in_single_quotes;
	int					in_double_quotes;
	struct s_token		*next;
}						t_token;

typedef struct s_quote
{
	int					in_single;
	int					in_double;
}						t_quote;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				**argv;
	t_redir				*redirs;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_shell
{
	char				**envp;
	char				**my_envp;
	int					last_exit_status;
}						t_shell;

typedef struct s_global
{
	struct termios			original_term;
	volatile sig_atomic_t	sigint_received;
}	t_global;

typedef struct s_argv_ctx
{
	char		**argv;
	int			i;
	t_token		*current;
	t_cmd		*cmd;
	t_shell		*shell;
}	t_argv_ctx;

t_token					*tokenize_with_quotes(char *input);
t_token					*extract_word_with_quotes(char *str, int *i);
t_token					*new_token(t_token_type type, char *value);
int						is_token_char(char c);
int						is_space(char c);
int						is_var_char(char c);
void					add_token(t_token **head, t_token *new);
void					print_tokens(t_token *tokens);
void					free_tokens(t_token *tokens);
void					free_commands(t_cmd *cmds);
t_cmd					*parse(t_token *tokens, t_shell *shell);
char					**build_argv(t_token **tokens, t_cmd *cmd,
							t_shell *shell);
t_cmd					*new_cmd(void);
void					print_commands(t_cmd *cmds);
int						is_redir(t_token_type type);
t_redir					*new_redir(int type, char *file);
void					add_redir(t_redir **head, t_redir *new);
t_redir					*parse_redir(t_token **tokens);
int						check_syntax(t_token *tokens);
char					*remove_quotes(char *str);

int						execute_cmds(t_cmd *cmds, t_shell *shell);

int						builtin_pwd(char **argv);
int						builtin_echo(char **argv);
int						builtin_cd(char **argv);
int						builtin_env(char **argv, t_shell *shell);
int						builtin_exit(char **argv);
int						builtin_export(char **argv, t_shell *shell);
int						builtin_unset(char **argv, t_shell *shell);
int						is_builtin(char *cmd);
int						exec_builtin(char **argv, t_shell *shell);

int						check_pipe_syntax(t_token *current);
int						check_redir_syntax(t_token *current);
void					free_redirs(t_redir *redir);
void					free_argv(char **argv);
void					add_word(t_token *curr, char **argv, int *i,
							t_shell *shell);
void					add_cmd(t_cmd **head, t_cmd *new);
int						count_args(t_token *tokens);
void					process_char_in_quotes(char *str, int *i, char *res,
							int *j);
int						handle_escape_in_dquotes(char *str, int *i, char *res,
							int *j);
char					*extract_normal_var(char *str, int start, int end);
void					add_pipe(t_token **tokens, int *i);
void					add_redir_out(t_token **tokens, char *input, int *i);
void					add_redir_in(t_token **tokens, char *input, int *i);
t_token					*init_token(void);
char					*copy_word(char *str, int start, int end);
void					process_word(char *str, int *i, t_quote *state);
char					*create_special_var(char c);
t_token					*create_var_token(t_token_type type, char c);
t_token					*handle_var(char *str, int *i);
void					update_quote_state(char c, t_quote *state,
							t_token *token);
int						process_redir(t_token **current, t_cmd *cmd);
t_redir					*new_redir(int type, char *file);

char					*expand_var(t_token *token, t_shell *shell);
char					*expand_word_with_vars(char *str, t_shell *shell);
char					*get_env_value(char *var_name, char **envp);
t_shell					*init_shell(char **envp);

int						count_env(char **envp);
char					**copy_envp(char **envp);
int						find_env_index(char **envp, char *var_name);
char					**set_env_var(char **envp, char *var_assign);
char					**unset_env_var(char **envp, char *var_name);
void					free_envp(char **envp);

int						has_unclosed_quotes(char *s);
char					*read_until_closed_quotes(char *line);
void					process_line(char *line_input, t_shell *shell);
void					clean_main(t_shell *shell);
void					restore_terminal(void);
char					**alloc_argv(t_token *tokens, int *i);
int						fill_argv(t_argv_ctx *ctx);
void					free_partial_argv(char **argv, int count);
void					setup_pipe(int prev_fd, int pipefd[2], int has_next);
char					*ft_strjoin3(const char *a, const char *b,
							const char *c);
void					apply_redir(t_redir *r);
void					apply_redirs(t_redir *redirs);
void					free_split(char **arr);
char					**dup_arr(const char *s, char **arr);
char					*substr_dup(const char *s, int start, int len);
int						has_slash(char *cmd);
char					*search_paths(char *cmd, char **paths);
int						exec_single_builtin(t_cmd *cmds, t_shell *sh);
int						fork_loop(t_cmd *cmds, t_shell *sh);
int						wait_children(void);
void					exec_child(t_cmd *cmd, t_shell *sh);
int						update_prev_fd(int prev_fd, int pipefd[2], int has_next);
#endif
