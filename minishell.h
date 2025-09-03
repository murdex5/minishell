/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:47 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/12 17:32:50 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
}						t_redirect_type;

typedef enum e_tokentype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
}						t_tokentype;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_SUBSHELL
}						t_node_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_ast_node
{
	t_node_type			type;
}						t_ast_node;

typedef struct s_command_node
{
	t_node_type			type;
	char				**argv;
	t_redirect			*redirections;
}						t_command_node;

typedef struct s_pipe_node
{
	t_node_type			type;
	t_ast_node			*left;
	t_ast_node			*right;
}						t_pipe_node;

typedef struct s_subshell_node
{
	t_node_type			type;
	struct s_ast_node	*child;
	t_redirect			*redirections;
}						t_subshell_node;

typedef struct s_token
{
	char				*value;
	t_tokentype			type;
	struct s_token		*next;
}						t_token;

char					**copy_environment(char *envp[]);
void					free_environment(char **msh_envp);
//int						is_builtin(t_command_node *node);
void					printf_err(char *msg, t_node_type type);
void					execve_error(t_command_node *cmd);
void					command_not_found(t_command_node *cmd);
void					perror_exit(char *msg, int i);
void					handle_left_child(int *pipe_fd, t_ast_node *node,
							char **envp);
void					handle_right_child(int *pipe_fd, t_ast_node *node,
							char **envp);
void					close2_fd(int fd1, int fd2);
int						perror_ret(char *msg, int i);
void					free_paths(char **paths);
int						close_exit(int fd1, int fd2, char **envp,
							t_ast_node *node);
int						exec_ast(t_ast_node *node, char **envp);
int						exec_pipe_node(t_pipe_node *pipe_node, char **envp);
int						exec_simple_command(t_command_node *cmd, char **envp);
void					handle_redirections(t_redirect *redir_list);
char					*resolve_command_path(const char *cmd_name,
							char **envp);
char					**get_path(char *env[]);
t_ast_node				*parse(t_token *token);
int						execute_ast_pipeline(t_ast_node *node, char **envp);
int						put_content(t_list *tmp, char **array, int *i);
t_redirect_type			get_redir_type(t_tokentype token_type);
void					free_ast(t_ast_node *node);
char					**list_to_array(t_list *lst);
t_pipe_node				*create_pipe_node(t_ast_node *left, t_ast_node *right);
bool					is_redirection(t_token *token);
void					advance_token(t_token **token);
t_redirect				*create_redirect(t_redirect_type type, char *filename);
void					add_redirect(t_redirect **list, t_redirect *new);
void					std_err_msg(char *msg);
t_token					*init_tokens(char *line);
t_token					*get_tokens(char **tokens);
void					specify_tokens(t_token *token);
int						get_array_len(char **tokens);
int						is_separator(char c);
int						count_words_shell(const char *s);
char					*get_next_word(const char **s);
int						free_on_error(char **result, int word_count);
void					free_tokens(char **tokens);
char					**construct_tokens(char *line);
void					free_on_exiting_list(t_token *tokens);
void					free_r1(char *r1);
void					ft_exit(char *r1, t_token *token);
void					*ft_realloc(void *a, size_t old_size, size_t new_size);
void					signal_handler(int sig);
int						process_signals(struct sigaction *sa);
#endif
