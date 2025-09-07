/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:21:02 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/07 16:21:05 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_env_variables(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	find_variable_index(char **envp, char *var_to_remove)
{
	int	i;
	int	var_len;

	var_len = ft_strlen(var_to_remove);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], var_to_remove, var_len) == 0
			&& (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	**allocate_new_envp(int size)
{
	char	**new_envp;

	new_envp = malloc(size * sizeof(char *));
	if (!new_envp)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	return (new_envp);
}
