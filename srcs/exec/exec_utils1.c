/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:03:48 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/20 00:55:32 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_cmd_path(char **cmd_path, t_command_node *cmd, char ***envp,
		t_ast_node *node)
{
	handle_redirections(cmd->redirections);
	*cmd_path = resolve_command_path(cmd->argv[0], *envp);
	if (!*cmd_path)
	{
		command_not_found(cmd);
		ft_exit_nomsg(*envp, node, 127);
	}
	execve(*cmd_path, cmd->argv, *envp);
	execve_error(cmd);
}

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
	int	fd_table[10];
	int	target_fd;
	int	new_fd;
	int	i;

	i = -1;
	while (++i < 10)
		fd_table[i] = -1;
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
