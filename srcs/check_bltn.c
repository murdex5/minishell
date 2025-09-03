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

int	check_cmd(t_command_node *node, char *envp[])
{
	char	**argv;

	argv = node->argv;
	printf("%s\n%s\n", node->argv[0], envp[0]);
	if (ft_strlcpy(argv[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strlcpy(argv[0], "cd", ft_strlen("cd")) == 0)
		return (2);
	else if (ft_strlcpy(argv[0], "pwd", ft_strlen("pwd")) == 0)
		return (3);
	else if (ft_strlcpy(argv[0], "export", ft_strlen("export")) == 0)
		return (4);
	else if (ft_strlcpy(argv[0], "unset", ft_strlen("unset")) == 0)
		return (5);
	else if (ft_strlcpy(argv[0], "env", ft_strlen("env")) == 0)
		return (6);
	else
		return (0);
}
