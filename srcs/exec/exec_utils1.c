/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:03:48 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/19 17:30:42 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static void	print_message(t_redirect *curr)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(curr->filename, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(strerror(errno), 2);
// 	ft_putstr_fd("\n", 2);
// }

void	handle_cmd_path(char **cmd_path, t_command_node *cmd, char ***envp,
		t_ast_node *node)
{
	handle_redirections(cmd->redirections);
	*cmd_path = resolve_command_path(cmd->argv[0], *envp);
	if (!*cmd_path)
	{
		command_not_found(cmd);
		ft_exit_builtin(*envp, node, cmd, 127);
	}
	execve(*cmd_path, cmd->argv, *envp);
	execve_error(cmd);
}

// int	open_file_based_on_type(t_redirect *redir)
// {
// 	int	fd;

// 	if (!redir || !redir->filename)
// 		return (-1);
// 	fd = -1;
// 	if (redir->type == REDIR_IN)
// 	{
// 		fd = open(redir->filename, O_RDONLY);
// 		if (fd == -1)
// 			perror_exit(redir->filename, 1);
// 	}
// 	else if (redir->type == REDIR_OUT)
// 	{
// 		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 			perror_exit(redir->filename, 1);
// 	}
// 	else if (redir->type == REDIR_APPEND)
// 	{
// 		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 			perror_exit(redir->filename, 1);
// 	}
// 	else if (redir->type == REDIR_HEREDOC)
// 	{
// 		fd = open(redir->filename, O_RDONLY);
// 		if (fd == -1)
// 			perror_exit("heredoc temp file", 1);
// 	}
// 	return (fd);
// }

static int	open_input_file(t_redirect *redir)
{
	int	fd;

	if (!redir || !redir->filename)
		return (-1);
	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		if (redir->type == REDIR_HEREDOC)
			perror_exit("heredoc temp file", 1);
		else
			perror_exit(redir->filename, 1);
	}
	return (fd);
}

static int	open_output_file(t_redirect *redir)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!redir || !redir->filename)
		return (-1);
	if (redir->type == REDIR_OUT)
		flags |= O_TRUNC;
	else if (redir->type == REDIR_APPEND)
		flags |= O_APPEND;
	fd = open(redir->filename, flags, 0644);
	if (fd == -1)
		perror_exit(redir->filename, 1);
	return (fd);
}

int	open_file_based_on_type(t_redirect *redir)
{
	if (!redir || !redir->filename)
		return (-1);
	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
		return (open_input_file(redir));
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (open_output_file(redir));
	return (-1);
}

void	handle_redirections(t_redirect *redirections)
{
	int	fd_table[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int	target_fd;
	int	new_fd;

	while (redirections)
	{
		if (redirections->type == REDIR_IN)
			target_fd = 0;
		else if (redirections->type == REDIR_OUT
			|| redirections->type == REDIR_APPEND)
			target_fd = 1;
		if (fd_table[target_fd] != -1)
		{
			close(fd_table[target_fd]);
			fd_table[target_fd] = -1;
		}
		new_fd = open_file_based_on_type(redirections);
		dup2(new_fd, target_fd);
		fd_table[target_fd] = new_fd;
		redirections = redirections->next;
	}
}
