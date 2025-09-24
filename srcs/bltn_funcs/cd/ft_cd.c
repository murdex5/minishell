/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:22 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/24 14:54:59 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	add_env_variable(char ***envp_ptr, const char *new_var_str)
{
	int		count;
	char	**new_envp;

	if (!envp_ptr || !*envp_ptr || !new_var_str)
		return (1);
	count = 0;
	while ((*envp_ptr)[count] != NULL)
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (perror("minishell: malloc failed"), 1);
	count = -1;
	while ((*envp_ptr)[++count] != NULL)
		new_envp[count] = (*envp_ptr)[count];
	new_envp[count] = ft_strdup(new_var_str);
	if (!new_envp[count])
	{
		free(new_envp);
		return (perror("minishell: ft_strdup failed"), 1);
	}
	new_envp[count + 1] = NULL;
	free(*envp_ptr);
	*envp_ptr = new_envp;
	return (0);
}

void	set_value(char ***envp_ptr, char *new_var_str, int i)
{
	(*envp_ptr)[i] = new_var_str;
}

void	update_env_var(char ***envp_ptr, const char *var_name,
		const char *value)
{
	size_t	name_len;
	size_t	value_len;
	char	*new_var_str;
	int		i;

	name_len = ft_strlen(var_name);
	value_len = ft_strlen(value);
	new_var_str = malloc(name_len + value_len + 2);
	if (!new_var_str)
		return (perror("minishell: malloc failed"));
	ft_memcpy(new_var_str, var_name, name_len);
	new_var_str[name_len] = '=';
	ft_memcpy(new_var_str + name_len + 1, value, value_len + 1);
	i = 0;
	while ((*envp_ptr)[i])
	{
		if (ft_strncmp((*envp_ptr)[i], var_name, name_len) == 0
			&& ((*envp_ptr)[i])[name_len] == '=')
			return (free((*envp_ptr)[i]), set_value(envp_ptr, new_var_str, i));
		i++;
	}
	if (add_env_variable(envp_ptr, new_var_str) != 0)
		perror("minishell: failed to add env variable");
	free(new_var_str);
}

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_cd(char **argv, char ***envp_ptr)
{
	char	old_pwd[PATH_MAX];
	char	*target_dir;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (perror("cd : getcwd error"), 1);
	target_dir = resolve_target_dir(argv, *envp_ptr);
	return (change_directory(target_dir, *envp_ptr, old_pwd));
}
