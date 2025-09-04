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

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_sorted_env(char **envp)
{
	char	**copy;
	int		i;
	int		j;
	char	*temp;

	copy = copy_environment(envp);
	if (!copy)
		return ;
	i = -1;
	while (copy[++i])
	{
		j = i;
		while (copy[++j])
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
			{
				temp = copy[i];
				copy[i] = copy[j];
				copy[j] = temp;
			}
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(copy[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free_environment(copy);
}

static int	update_existing_var(char ***envp_ptr, char *new_var)
{
	int		i;
	size_t	name_len;
	char	*equals_pos;

	equals_pos = ft_strchr(new_var, '=');
	if (!equals_pos)
		name_len = ft_strlen(new_var);
	else
		name_len = equals_pos - new_var;
	i = -1;
	while ((*envp_ptr)[++i])
	{
		if (ft_strncmp((*envp_ptr)[i], new_var, name_len) == 0
			&& ((*envp_ptr)[i])[name_len] == '=')
		{
			free((*envp_ptr)[i]);
			(*envp_ptr)[i] = ft_strdup(new_var);
			if (!(*envp_ptr)[i])
				return (-1);
			return (1);
		}
	}
	return (0);
}

static int	add_new_var(char ***envp_ptr, char *new_var)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while ((*envp_ptr)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (0);
	i = -1;
	while (++i < count)
		new_env[i] = (*envp_ptr)[i];
	new_env[count] = ft_strdup(new_var);
	if (!new_env[count])
	{
		free(new_env);
		return (0);
	}
	new_env[count + 1] = NULL;
	free(*envp_ptr);
	*envp_ptr = new_env;
	return (1);
}

int	ft_export(char **argv, char ***envp_ptr)
{
	int	i;
	int	ret;

	if (!argv[1])
	{
		print_sorted_env(*envp_ptr);
		return (0);
	}
	i = 0;
	ret = 0;
	while (argv[++i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret = 1;
			continue;
		}
		if (update_existing_var(envp_ptr, argv[i]) == -1)
			return (1);
		if (!update_existing_var(envp_ptr, argv[i])
			&& !add_new_var(envp_ptr, argv[i]))
			return (1);
	}
	return (ret);
}
