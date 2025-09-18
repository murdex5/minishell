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
int open_file_based_on_type(t_redirect *redir)
{
    int fd;

    if (!redir || !redir->filename)
        return (-1);

    fd = -1;
    if (redir->type == REDIR_IN)
    {
        fd = open(redir->filename, O_RDONLY);
        if (fd == -1)
            perror_exit(redir->filename, 1);
    }
    else if (redir->type == REDIR_OUT)
    {
        fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            perror_exit(redir->filename, 1);
    }
    else if (redir->type == REDIR_APPEND)
    {
        fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            perror_exit(redir->filename, 1);
    }
    else if (redir->type == REDIR_HEREDOC)
    {
        // For heredoc, you would have already processed the content
        // and stored it in a temporary file, so you'd open that file
        fd = open(redir->filename, O_RDONLY);
        if (fd == -1)
            perror_exit("heredoc temp file", 1);
    }

    return (fd);
}

void handle_redirections(t_redirect *redirections)
{
    int fd_table[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Track open fds
    
    while (redirections)
    {
        int target_fd;
        int new_fd;
        
        // Determine target fd based on redirection type
        if (redirections->type == REDIR_IN)
            target_fd = 0; // STDIN_FILENO
        else if (redirections->type == REDIR_OUT || redirections->type == REDIR_APPEND)
            target_fd = 1; // STDOUT_FILENO
            
        // If we already have this fd open from a previous redirection, close it
        if (fd_table[target_fd] != -1)
        {
            close(fd_table[target_fd]);
            fd_table[target_fd] = -1;
        }
        
        // Open the new file and save its fd
        new_fd = open_file_based_on_type(redirections);
        
        // Redirect and keep track of the open fd
        dup2(new_fd, target_fd);
        fd_table[target_fd] = new_fd;
        
        redirections = redirections->next;
    }
}
