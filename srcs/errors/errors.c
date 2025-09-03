/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:42:06 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/31 10:42:07 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	perror_ret(char *msg, int i)
{
	perror(msg);
	return (i);
}

void	command_not_found(t_command_node *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 20);
}

void	execve_error(t_command_node *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", ft_strlen("\n"));
}

void	printf_err(char *msg, t_node_type type)
{
	write(2, msg, ft_strlen(msg));
	write(2, " - Type: ", 9);
	ft_putnbr_fd(type, 2);
	write(2, "\n", 1);
}
