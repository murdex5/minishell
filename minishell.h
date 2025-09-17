/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:47 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/09 15:39:54 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_redirect_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_NONE
}								t_redirect_type;

typedef enum e_tokentype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
}								t_tokentype;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_SUBSHELL
}								t_node_type;

typedef struct s_redirect
{
	t_redirect_type				type;
	char						*filename;
	struct s_redirect			*next;
}								t_redirect;

typedef struct s_ast_node
{
	t_node_type					type;
}								t_ast_node;

typedef struct s_command_node
{
	t_node_type					type;
	char						**argv;
	t_redirect					*redirections;
}								t_command_node;

typedef struct s_pipe_node
{
	t_node_type					type;
	t_ast_node					*left;
	t_ast_node					*right;
}								t_pipe_node;

typedef struct s_subshell_node
{
	t_node_type					type;
	struct s_ast_node			*child;
	t_redirect					*redirections;
}								t_subshell_node;

typedef struct s_token
{
	char						*value;
	t_tokentype					type;
	struct s_token				*next;
}								t_token;

typedef struct s_expand_data
{
	char						*result;
	char						***envp_ptr;
	int							exit_code;
	int							j;
}								t_expand_data;

typedef struct s_shell_state
{
	char						**envp_copy;
	int							exit_code;
	struct termios				original_term;
	t_ast_node					*pipe;
	int							temp_exit;
}								t_shell_state;

extern volatile sig_atomic_t	g_signal_received;

/* ** BUILT IN FUNCS ** */
/*  ft_expand_vars */
void							expand_token_variables(t_token *tokens,
									int exit, char ***envp_ptr);
/* ft_echo */
int								ft_echo(char **argv);
int								check_on_evnp(char *variable_name, char **envp);
char							*get_variable_value(int index, char **envp_ptr);
char							*modify_variable(char *str);
char							*detect_varaible_name(char *argv);
int								validate_quotes(const char *str);
char							*process_arguments(const char *str);
int								append_str(char *dest, int start_index,
									const char *src);
void							find_quote(const char *str, char *processed_str,
									int quote);
int								append_to_result(char *result, int j,
									char *str_to_append);
int								handle_special_vars(char *str, int *i,
									t_expand_data *data);
int								handle_env_var_expansion(char *var_name,
									t_expand_data *data);
int								handle_regular_vars(char *str, int *i,
									t_expand_data *data);
int								process_dollar_sign(char *str, int *i,
									t_expand_data *data);
char							*expand_and_replace_vars(char *str,
									char ***envp_ptr, int exit_code);
/* ft_cd */
int								ft_cd(char **argv, char ***envp);
/* ft_pwd */
int								ft_pwd(void);
/* ft_export */
void							sort_envp(char **copy_envp);
int								check_exists(char **argv, char **envp);
char							*get_variable_name(char **argv);
int								count_envp(char **envp);
int								check_args(char *argv);
void							print_envp(char **envp);
int								ft_export(char **argv, char ***envp_ptr);
/* FT_UNSET */
int								count_env_variables(char **envp);
int								ft_unset(char **argv, char ***envp);
int								find_variable_index(char **envp,
									char *var_to_remove);
void							free_redirects(t_redirect *redir);
void							free_til(char **tokens, int i);
char							**allocate_new_envp(int size);
int								ft_env(char **envp);
t_token							*handle_new(t_token *head, int i,
									char **tokens);
int								exec_ast(t_ast_node *node, char ***envp,
									t_ast_node *root_node);
int								exec_simple_command(t_command_node *cmd,
									char ***envp, t_ast_node *root_node);
int								exec_pipe_node(t_pipe_node *pipe_node,
									char ***envp, t_ast_node *root_node);
void							handle_left_child(int *pipe_fd,
									t_ast_node *node, char **envp,
									t_ast_node *root_node);
void							handle_right_child(int *pipe_fd,
									t_ast_node *node, char **envp,
									t_ast_node *root_node);
void							save_terminal_state(struct termios
									*original_state);
void							restore_terminal_state(struct termios
									*original_state);
int								ft_strcmp(const char *s1, const char *s2);
void							initialize_shell(t_shell_state *state,
									char *envp[]);
void							process_line(char *line, t_shell_state *state);
void							shell_loop(t_shell_state *state);
void							cleanup_shell(t_shell_state *state);
void							free_pipe(t_ast_node *node);
void							handle_redirections(t_redirect *redir_list);
void							handle_cmd_path(char **cmd_path,
									t_command_node *cmd, char ***envp,
									t_ast_node *node);
int								ft_exit_builtin(char **envp, t_ast_node *pipe,
									int code);

void							free_token(t_token *token);
char							*ft_strcpy(char *dest, const char *src);
char							*ft_strstr(const char *haystack,
									const char *needle);
int								execute_builtin(t_command_node *cmd,
									char ***envp, t_ast_node *pipe);
char							**copy_environment(char *envp[]);
void							free_environment(char **msh_envp);
int								is_builtin(t_command_node *node);
void							printf_err(char *msg, t_node_type type);
void							execve_error(t_command_node *cmd);
void							command_not_found(t_command_node *cmd);
void							perror_exit(char *msg, int i);

void							close2_fd(int fd1, int fd2);
int								perror_ret(char *msg, int i);
void							free_paths(char **paths);
int								close_exit(int fd1, int fd2, char **envp,
									t_ast_node *node);

void							handle_redirections(t_redirect *redir_list);
char							*resolve_command_path(const char *cmd_name,
									char **envp);
char							**get_path(char *env[]);
t_ast_node						*parse(t_token *token);
int								execute_ast_pipeline(t_ast_node *node,
									char ***envp_ptr);
int								put_content(t_list *tmp, char **array, int *i);
t_redirect_type					get_redir_type(t_tokentype token_type);
void							free_ast(t_ast_node *node);
char							**list_to_array(t_list *lst);
t_pipe_node						*create_pipe_node(t_ast_node *left,
									t_ast_node *right);
bool							is_redirection(t_token *token);
void							advance_token(t_token **token);
t_redirect						*create_redirect(t_redirect_type type,
									char *filename);
void							add_redirect(t_redirect **list,
									t_redirect *new);
void							std_err_msg(char *msg);
t_token							*init_tokens(char *line);
t_token							*get_tokens(char **tokens);
void							specify_tokens(t_token *token);
int								get_array_len(char **tokens);
int								is_separator(char c);
int								count_words_shell(const char *s);
char							*get_next_word(const char **s);
int								free_on_error(char **result, int word_count);
void							free_tokens(char **tokens);
char							**construct_tokens(char *line);
void							free_on_exiting_list(t_token *tokens);
void							free_r1(char *r1);
void							ft_exit(char *r1, t_token *token,
									char **envp_ptr, t_ast_node *pipe);
void							*ft_realloc(void *a, size_t old_size,
									size_t new_size);
void							signal_handler(int sig);
int								process_signals(struct sigaction *sa);
int								is_single_quoted(const char *str);

#endif
