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

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_env_var(char *var)
{
	char	*equals;
	int		name_len;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	equals = ft_strchr(var, '=');
	if (equals)
	{
		name_len = equals - var;
		write(STDOUT_FILENO, var, name_len + 1);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(equals + 1, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(var, STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	if (envp)
	{
		while (envp[count])
			count++;
	}
	return (count);
}

static void	copy_env_recursive(char **dest, char **src, int index)
{
	if (!src || !src[index])
		return;
	dest[index] = src[index];
	copy_env_recursive(dest, src, index + 1);
}

static void	bubble_sort_recursive(char **arr, int n, int i, int j)
{
	char	*temp;

	if (i >= n - 1)
		return;
	if (j >= n - i - 1)
	{
		bubble_sort_recursive(arr, n, i + 1, 0);
		return;
	}
	if (ft_strcmp(arr[j], arr[j + 1]) > 0)
	{
		temp = arr[j];
		arr[j] = arr[j + 1];
		arr[j + 1] = temp;
	}
	bubble_sort_recursive(arr, n, i, j + 1);
}

static void	print_sorted_env_recursive(char **envp, int index, int count)
{
	if (index >= count)
		return;
	print_env_var(envp[index]);
	print_sorted_env_recursive(envp, index + 1, count);
}

static void	sort_and_print_env(char **envp)
{
	int		count;
	char	**env_copy;

	count = count_env_vars(envp);
	if (count == 0)
		return;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return;
	copy_env_recursive(env_copy, envp, 0);
	env_copy[count] = NULL;
	bubble_sort_recursive(env_copy, count, 0, 0);
	print_sorted_env_recursive(env_copy, 0, count);
	free(env_copy);
}

static char	**find_env_var_recursive(char **env, const char *name, size_t name_len, int index)
{
	if (!env || !env[index])
		return (NULL);
	if (ft_strncmp(env[index], name, name_len) == 0 && 
		(env[index][name_len] == '=' || env[index][name_len] == '\0'))
		return (&env[index]);
	return (find_env_var_recursive(env, name, name_len, index + 1));
}

static int	add_or_update_env_var(t_shell *shell, const char *var)
{
	char	*equals;
	size_t	name_len;
	char	**var_ptr;
	char	**new_env;
	int		count;
	int		i;

	equals = ft_strchr(var, '=');
	name_len = equals ? (size_t)(equals - var) : ft_strlen(var);
	var_ptr = find_env_var_recursive(shell->env, var, name_len, 0);
	
	if (var_ptr && shell->env_copied)
	{
		free(*var_ptr);
		*var_ptr = ft_strdup(var);
		return (*var_ptr ? 0 : 1);
	}
	
	count = count_env_vars(shell->env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	
	i = -1;
	while (++i < count)
		new_env[i] = shell->env[i];
	
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	
	if (shell->env_copied)
		free(shell->env);
	
	shell->env = new_env;
	shell->env_copied = 1;
	return (0);
}

static int	process_export_args(t_shell *shell, char **argv, int index, int *ret)
{
	if (!argv[index])
		return (*ret);
	
	if (!is_valid_identifier(argv[index]))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(argv[index], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		*ret = 1;
		return (process_export_args(shell, argv, index + 1, ret));
	}
	
	if (add_or_update_env_var(shell, argv[index]) != 0)
	{
		ft_putstr_fd("export: memory allocation error\n", STDERR_FILENO);
		return (1);
	}
	
	return (process_export_args(shell, argv, index + 1, ret));
}

int	ft_export(char **argv, t_shell *shell)
{
	int	ret;

	if (!argv[1])
	{
		sort_and_print_env(shell->env);
		return (0);
	}
	
	ret = 0;
	return (process_export_args(shell, argv, 1, &ret));
}