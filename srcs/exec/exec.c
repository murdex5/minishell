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

int	execute_ast_pipeline(t_ast_node *node, char **envp)
{
	if (!node)
		return (0);
	return (exec_ast(node, envp));
}

int	exec_ast(t_ast_node *node, char **envp)
{
	if (node->type == NODE_COMMAND)
	{
		return (exec_simple_command((t_command_node *)node, envp));
	}
	if (node->type == NODE_PIPE)
		return (exec_pipe_node((t_pipe_node *)node, envp));
	printf_err("minishell: Unrecognized node type", node->type);
	return (127);
}

int	exec_simple_command(t_command_node *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
		return (perror_ret("fork", 1));
	if (pid == 0)
	{
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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

int	exec_pipe_node(t_pipe_node *pipe_node, char **envp)
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
		handle_left_child(fd, pipe_node->left, envp);
	pid_right = fork();
	if (pid_right == -1)
		return (perror_ret("fork", 1));
	if (pid_right == 0)
		handle_right_child(fd, pipe_node->right, envp);
	close2_fd(fd[0], fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (128 + WTERMSIG(status_right));
}

void	handle_redirections(t_redirect *redir_list)
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
			perror_exit(curr->filename, 1);
		if (curr->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		curr = curr->next;
	}
}
