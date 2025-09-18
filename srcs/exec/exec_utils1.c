/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:03:48 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/16 22:03:50 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_message(t_redirect *curr)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(curr->filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

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

int	handle_redirections(t_redirect *redir_list)
{
	t_redirect	*curr;
	int			in_fd;
	int			out_fd;
	int			temp_fd;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	curr = redir_list;
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_HEREDOC)
		{
			temp_fd = open(curr->filename, O_RDONLY);
			if (temp_fd < 0)
			{
				print_message(curr);
				if (in_fd != STDIN_FILENO) close(in_fd);
				if (out_fd != STDOUT_FILENO) close(out_fd);
				return (1);
			}
			if (in_fd != STDIN_FILENO) close(in_fd);
			in_fd = temp_fd;
		}
		else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
		{
			if (curr->type == REDIR_OUT)
				temp_fd = open(curr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else // REDIR_APPEND
				temp_fd = open(curr->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

			if (temp_fd < 0)
			{
				print_message(curr);
				if (in_fd != STDIN_FILENO) close(in_fd);
				if (out_fd != STDOUT_FILENO) close(out_fd);
				return (1);
			}
			if (out_fd != STDOUT_FILENO) close(out_fd);
			out_fd = temp_fd;
		}
		curr = curr->next;
	}

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return (0);
}
