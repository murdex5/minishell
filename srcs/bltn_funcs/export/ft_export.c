/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:41:13 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/03 11:41:14 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_variable_name(char **argv)
{
	char	*variable_name;
	int		i;
	int		count;

	if (!argv || !argv[1])
		return (NULL);
	i = 0;
	while (argv[1][i] && argv[1][i] != '=')
		i++;
	count = i;
	variable_name = malloc(sizeof(char) * (count + 1));
	if (!variable_name)
		return (NULL);
	i = 0;
	while (i < count)
	{
		variable_name[i] = argv[1][i];
		i++;
	}
	variable_name[count] = '\0';
	return (variable_name);
}

int	add_new_variable(char ***envp_ptr, const char *new_var_str)
{
	char	**new_envp;
	int		count;
	int		i;

	count = 0;
	while ((*envp_ptr)[count])
		count++;
	new_envp = malloc((count + 2) * sizeof(char *));
	if (!new_envp)
		return (perror("minishell: malloc"), 0);
	i = 0;
	while (i < count)
	{
		new_envp[i] = (*envp_ptr)[i];
		i++;
	}
	new_envp[count] = ft_strdup(new_var_str);
	if (!new_envp[count])
		return (perror("minishell: ft_strdup"), free(new_envp), 0);
	new_envp[count + 1] = NULL;
	free(*envp_ptr);
	*envp_ptr = new_envp;
	return (1);
}

void	sort_envp(char **copy_envp)
{
	int		i;
	int		sorted;
	char	*temp;

	if (!copy_envp || !copy_envp[0])
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 1;
		while (copy_envp[i])
		{
			if (ft_strncmp(copy_envp[i], copy_envp[i - 1],
					ft_strlen(copy_envp[i])) < 0)
			{
				temp = copy_envp[i];
				copy_envp[i] = copy_envp[i - 1];
				copy_envp[i - 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}

int	update_envp(char ***envp_ptr, char **argv)
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
		if (!add_new_variable(envp_ptr, argv[1]))
			return (1);
	}
	return (0);
}

int	ft_export(char **argv, char ***envp_ptr)
{
	if (argv[1] == NULL)
	{
		print_envp(*envp_ptr);
		return (0);
	}
	if (!check_args(argv[1]))
		return (1);
	if (update_envp(envp_ptr, argv))
		return (1);
	return (0);
}
