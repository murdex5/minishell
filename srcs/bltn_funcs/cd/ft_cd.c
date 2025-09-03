/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:22 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/03 11:27:06 by kadferna         ###   ########.fr       */
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
	{
		perror("minishell: malloc failed");
		return (1);
	}
	count = 0;
	while ((*envp_ptr)[count] != NULL)
	{
		new_envp[count] = (*envp_ptr)[count];
		count++;
	}
	new_envp[count] = ft_strdup(new_var_str);
	if (!new_envp[count])
	{
		perror("minishell: ft_strdup failed");
		free(new_envp); 
		return (1);
	}
	new_envp[count + 1] = NULL;

	free(*envp_ptr);
	*envp_ptr = new_envp;
	return (0);
}

void	update_env_var(char ***envp_ptr, const char *var_name,
		const char *value)
{
	int		i;
	char	*new_var_str;
	size_t	name_len;
	size_t	value_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while ((*envp_ptr)[i])
	{
		if (ft_strncmp((*envp_ptr)[i], var_name, name_len) == 0
			&& ((*envp_ptr)[i])[name_len] == '=')
		{
			free((*envp_ptr)[i]);
			value_len = ft_strlen(value);
			new_var_str = malloc(name_len + value_len + 2);
			if (!new_var_str)
				return ; // Malloc failure
			ft_memcpy(new_var_str, var_name, name_len);
			new_var_str[name_len] = '=';
			ft_memcpy(new_var_str + name_len + 1, value, value_len + 1);
			(*envp_ptr)[i] = new_var_str;
			return ;
		}
		i++;
	}
	// If we are here, the variable was not found, so we should add it.
	value_len = ft_strlen(value);
	new_var_str = malloc(name_len + value_len + 2);
	if (!new_var_str)
		return ; // Malloc failure
	ft_memcpy(new_var_str, var_name, name_len);
	new_var_str[name_len] = '=';
	ft_memcpy(new_var_str + name_len + 1, value, value_len + 1);
	add_env_variable(envp_ptr, new_var_str);
	free(new_var_str); // add_env_variable should make its own copy
}

int	ft_cd(char **argv, char **envp)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (perror("cd : getcwd error"), 1);
	if (argv[1] == NULL)
	{
		ft_putstr_fd("cd : missing arguments\n", STDERR_FILENO);
		return (1);
	}
	if (argv[2] != NULL)
	{
		ft_putstr_fd("cd : too many argumetns\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	update_env_var(&envp, "OLDPWD", old_pwd);
	update_env_var(&envp, "PWD", new_pwd);
	return(0);
}
