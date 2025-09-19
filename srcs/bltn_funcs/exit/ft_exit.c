/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:09:06 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/03 13:09:08 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_arg_value(char *str)
{
	size_t	i;
	int		exit_code;

	i = ft_strlen(str);
	exit_code = ft_atoi(str);
	if (i > 0 && exit_code == 0)
	{
		ft_putstr_fd("minishell : numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	return (exit_code);
}

int	ft_exit_builtin(char **envp, t_ast_node *pipe, t_command_node *cmd,
		int code)
{
	int	exit_code;

	exit_code = 0;
	if (cmd)
	{
		if (argv_list_len(cmd->argv) == 2)
			exit_code = check_arg_value(cmd->argv[1]);
		else if (argv_list_len(cmd->argv) > 2)
		{
			ft_putstr_fd("minishell : too many argumens\n", STDERR_FILENO);
			exit_code = 1;
		}
	}
	free_environment(envp);
	free_ast(pipe);
	printf("exit\n");
	if (code > 0)
		exit_code = code;
	if (exit_code > 255)
		exit_code = modulo_val(exit_code);
	exit(exit_code);
	return (exit_code);
}

int	ft_exit_nomsg(char **envp, t_ast_node *pipe, int code)
{
	int	exit_code;

	exit_code = 0;
	free_environment(envp);
	free_ast(pipe);
	if (code > 0)
		exit_code = code;
	exit(exit_code);
	return (exit_code);
}
