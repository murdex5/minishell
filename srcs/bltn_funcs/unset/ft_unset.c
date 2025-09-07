/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:24:30 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/05 14:24:34 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	copy_variables(char **new_envp, char **old_envp, int remove_idx, int count)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < count)
	{
		if (i != remove_idx)
		{
			new_envp[j] = old_envp[i];
			j++;
		}
		else
			free(old_envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	return (1);
}

int	remove_variable(char ***envp_ptr, char *var_to_remove)
{
	char	**new_envp;
	int		count;
	int		remove_idx;

	count = count_env_variables(*envp_ptr);
	remove_idx = find_variable_index(*envp_ptr, var_to_remove);
	if (remove_idx == -1)
		return (1);
	new_envp = allocate_new_envp(count);
	if (!new_envp)
		return (0);
	copy_variables(new_envp, *envp_ptr, remove_idx, count);
	free(*envp_ptr);
	*envp_ptr = new_envp;
	return (1);
}

int	ft_unset(char **argv, char ***envp)
{
	int	i;

	if (!argv[1])
	{
		ft_putstr_fd("unset: missing variable name\n", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!remove_variable(envp, argv[i]))
			return (1);
		i++;
	}
	return (0);
}
