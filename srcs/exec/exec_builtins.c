/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:03:36 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/03 11:04:45 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin(t_command_node *cmd, char ***envp, t_ast_node *pipe)
{
	char	*cmd_name;

	cmd_name = cmd->argv[0];
	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name)) == 0)
		return (ft_echo(cmd->argv));
	if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name)) == 0)
		return (ft_cd(cmd->argv, envp));
	if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
		return (ft_export(cmd->argv, envp));
	if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
		return (ft_unset(cmd->argv, envp));
	if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name)) == 0)
		return (ft_env(*envp));
	if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
		return (ft_exit_builtin(*envp, pipe, 0));
	return (0);
}
