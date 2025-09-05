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

int	remove_variable(char ***envp_ptr, char *var_to_remove)
{
	char	**new_envp;
	int		count;
	int		old_idx;
	int		new_idx;
	int		remove_idx;

	remove_idx = check_on_evnp(var_to_remove, *envp_ptr);
	if (remove_idx == -1)
		return (1);
	count = 0;
	while ((*envp_ptr)[count])
		count++;
	new_envp = malloc(count * sizeof(char *));
	if (!new_envp)
	{
		perror("minishell: malloc");
		return (0); // Failure
	}
	old_idx = 0;
	new_idx = 0;
	while (old_idx < count)
	{
		if (old_idx == remove_idx)
			free((*envp_ptr)[old_idx]);
		else
		{
			new_envp[new_idx] = (*envp_ptr)[old_idx];
			new_idx++;
		}
		old_idx++;
	}
	new_envp[new_idx] = NULL;
	free(*envp_ptr);
	*envp_ptr = new_envp;
	return (1); // Success
}

int	update_envp_remove(char ***envp_ptr, char **argv)
{
	int	exists_index;

	exists_index = check_exists(argv, *envp_ptr);
	if (exists_index >= 0)
	{
		free((*envp_ptr)[exists_index]);
		(*envp_ptr)[exists_index] = ft_strdup(argv[1]);
		if (!(*envp_ptr)[exists_index])
			return (1);
	}
	else
	{
		if (!remove_variable(envp_ptr, argv[1]))
			return (1);
	}
	return (0);
}

int	ft_unset(char **argv, char ***envp)
{
	int	i;

	i = check_exists(argv, *envp);
	if (i < 0)
		return (1);
	if (update_envp_remove(envp, argv))
		return (1);
	return (0);
}
