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
		ft_exit_builtin(*envp, node, 127);
	}
	execve(*cmd_path, cmd->argv, *envp);
	execve_error(cmd);
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
			return (print_message(curr));
		if (curr->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		curr = curr->next;
	}
}
