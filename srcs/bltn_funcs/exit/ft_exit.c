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

int	ft_exit_builtin(char **argv, t_token *token, char *line)
{
	int exit_code;

	exit_code = 0;
	if (argv[1])
	{
		if (!ft_isdigit_str(argv[1]))
		{
			ft_putstr_fd("exit: numeric argment required\n", STDERR_FILENO);
			exit_code = 2;
		}
		else
			exit_code = ft_atoi(argv[1]);
	}
	ft_exit(line, token);
	exit(exit_code);
	return (exit_code);
}
