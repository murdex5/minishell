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

int	execute_ast_pipeline(t_ast_node *node, char ***envp_ptr)
{
	int	result;

	if (!node)
		return (0);
	result = exec_ast(node, envp_ptr, node);
	free_ast(node);
	return (result);
}

int	exec_ast(t_ast_node *node, char ***envp, t_ast_node *root_node)
{
	if (node->type == NODE_COMMAND)
	{
		return (exec_simple_command((t_command_node *)node, envp, root_node));
	}
	if (node->type == NODE_PIPE)
		return (exec_pipe_node((t_pipe_node *)node, envp, root_node));
	printf_err("minishell: Unrecognized node type", node->type);
	return (127);
}

int	exec_blt_command(t_command_node *cmd, char ***envp, t_ast_node *node)
{
	int	stdout_backup;
	int	stdin_backup;
	int	result;

	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	errno = 0;
	handle_redirections(cmd->redirections);
	if (errno != 0)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		dup2(stdin_backup, STDIN_FILENO);
		close(stdout_backup);
		close(stdin_backup);
		return (1);
	}
	result = execute_builtin(cmd, envp, node);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdout_backup);
	close(stdin_backup);
	return (result);
}

int	exec_simple_command(t_command_node *cmd, char ***envp,
		t_ast_node *root_node)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	int		builtin_type;

	builtin_type = is_builtin(cmd);
	cmd_path = NULL;
	if (builtin_type > 0)
		return (exec_blt_command(cmd, envp, root_node));
	pid = fork();
	if (pid == -1)
		return (perror_ret("fork", 1));
	if (pid == 0)
	{
		handle_cmd_path(&cmd_path, cmd, envp, root_node);
		free(cmd_path);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

int	exec_pipe_node(t_pipe_node *pipe_node, char ***envp, t_ast_node *root_node)
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
		handle_left_child(fd, pipe_node->left, *envp, root_node);
	pid_right = fork();
	if (pid_right == -1)
		return (perror_ret("fork", 1));
	if (pid_right == 0)
		handle_right_child(fd, pipe_node->right, *envp, root_node);
	close2_fd(fd[0], fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (128 + WTERMSIG(status_right));
}
