/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bltn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:50:20 by kadferna          #+#    #+#             */
/*   Updated: 2025/08/21 22:50:25 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_command_node *node)
{
	char	*cmd_name;

	if (!node || !node->argv || !node->argv[0])
		return (0);
	cmd_name = node->argv[0];
	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name) + 1) == 0)
		return (2);
	if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name) + 1) == 0)
		return (3);
	if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name) + 1) == 0)
		return (4);
	if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name) + 1) == 0)
		return (5);
	if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name) + 1) == 0)
		return (6);
	if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name) + 1) == 0)
		return (7);
	return (0);
}
