/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:11:49 by kadferna          #+#    #+#             */
/*   Updated: 2025/08/05 17:11:52 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*process_path(char **paths, const char *cmd_name)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*resolve_command_path(const char *cmd_name, char **envp)
{
	char	**paths;
	char	*full_path;

	if (!cmd_name || !*cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	paths = get_path(envp);
	if (!paths)
		return (NULL);
	full_path = process_path(paths, cmd_name);
	if (full_path != NULL)
		return (full_path);
	free_paths(paths);
	return (NULL);
}

void	handle_left_child(int *pipe_fd, t_ast_node *node, char **envp)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	exit(exec_ast(node, envp));
}

void	handle_right_child(int *pipe_fd, t_ast_node *node, char **envp)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	exit(exec_ast(node, envp));
}

char	**get_path(char *env[])
{
	char	**paths;
	char	*path_env;

	path_env = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path_env = *env;
			break ;
		}
		env++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env + 5, ':');
	return (paths);
}
