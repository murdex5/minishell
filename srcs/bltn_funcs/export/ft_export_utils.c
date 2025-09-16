/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:50:52 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/16 20:50:55 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	check_args(char *argv)
{
	if (argv[0] >= '0' && argv[0] <= '9')
	{
		ft_putstr_fd("export : ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd(" is not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	sort_envp(envp);
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	check_exists(char **argv, char **envp)
{
	int		i;
	char	*variable_name;
	size_t	len;

	variable_name = get_variable_name(argv);
	if (!variable_name || *variable_name == '\0')
	{
		if (variable_name)
			free(variable_name);
		return (-1);
	}
	len = ft_strlen(variable_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(variable_name, envp[i], len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
		{
			free(variable_name);
			return (i);
		}
		i++;
	}
	free(variable_name);
	return (-1);
}
