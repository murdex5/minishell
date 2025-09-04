/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:06:46 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/25 11:06:47 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_ast_pipeline(t_ast_node *node, char ***envp_ptr, t_token *token,
		char *line)
{
	int	result;

	if (!node)
		return (0);
	result = exec_ast(node, *envp_ptr, token, line);
	free_ast(node);
	return (result);
}

int	exec_ast(t_ast_node *node, char **envp, t_token *token, char *line)
{
	if (node->type == NODE_COMMAND)
	{
		return (exec_simple_command((t_command_node *)node, envp, token, line));
	}
	if (node->type == NODE_PIPE)
		return (exec_pipe_node((t_pipe_node *)node, envp, token, line));
	printf_err("minishell: Unrecognized node type", node->type);
	return (127);
}

int	exec_simple_command(t_command_node *cmd, char **envp, t_token *token,
		char *line)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	int     builtin_type;

	// Check if it's a builtin first
	builtin_type = is_builtin(cmd);
	if (builtin_type > 0)
	{
		// For builtins, we handle redirections and execute in the current process
		int stdout_backup = dup(STDOUT_FILENO);
		int stdin_backup = dup(STDIN_FILENO);
		
		// Setup redirections - we'll use global errno to check for errors
		errno = 0;
		handle_redirections(cmd->redirections);
		
		if (errno != 0)
		{
			// Redirection failed, restore original file descriptors
			dup2(stdout_backup, STDOUT_FILENO);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdout_backup);
			close(stdin_backup);
			return (1);
		}
		
		// Execute the builtin
		int result = execute_builtin(cmd, &envp, token, line);
		
		// Restore standard file descriptors
		dup2(stdout_backup, STDOUT_FILENO);
		dup2(stdin_backup, STDIN_FILENO);
		close(stdout_backup);
		close(stdin_backup);
		
		return result;
	}

	// For non-builtins, fork and execute
	pid = fork();
	if (pid == -1)
		return (perror_ret("fork", 1));
	
	if (pid == 0)
	{
		// Child process
		handle_redirections(cmd->redirections);
		cmd_path = resolve_command_path(cmd->argv[0], envp);
		if (!cmd_path)
		{
			command_not_found(cmd);
			exit(127);
		}
		execve(cmd_path, cmd->argv, envp);
		execve_error(cmd);
		free(cmd_path);
		exit(126);
	}
	
	// Parent process
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

int	exec_pipe_node(t_pipe_node *pipe_node, char **envp, t_token *token,
		char *line)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_right;

	if (pipe(fd) == -1)
		return (perror_ret("pipe", 1));
	pid_left = fork();
	if (pid_left == -1)
		return (perror_ret("fork", 1));
	if (pid_left == 0)
		handle_left_child(fd, pipe_node->left, envp, token, line);
	pid_right = fork();
	if (pid_right == -1)
		return (perror_ret("fork", 1));
	if (pid_right == 0)
		handle_right_child(fd, pipe_node->right, envp, token, line);
	close2_fd(fd[0], fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (128 + WTERMSIG(status_right));
}

void handle_redirections(t_redirect *redir_list)
{
	t_redirect	*curr;
	int			fd;

	curr = redir_list;
	while (curr)
	{
		if (curr->type == REDIR_OUT)
			fd = open(curr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (curr->type == REDIR_IN)
			fd = open(curr->filename, O_RDONLY);
		else if (curr->type == REDIR_APPEND)
			fd = open(curr->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = -1;
		
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(curr->filename, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return; // Return early on error, errno will be set
		}
		
		if (curr->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
			dup2(fd, STDOUT_FILENO);
			
		close(fd);
		curr = curr->next;
	}
}
