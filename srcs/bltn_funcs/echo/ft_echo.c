/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:08 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/15 09:58:30 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*process_arguments(const char *str)
{
	char	*processed_str;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	processed_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!processed_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				processed_str[j++] = str[i];
			i++;
			continue ;
		}
		else
			processed_str[j++] = str[i++];
	}
	processed_str[j] = '\0';
	return (processed_str);
}

int	check_on_evnp(char *variable_name, char **envp)
{
	int		i;
	size_t	len;

	if (!variable_name || *variable_name == '\0')
	{
		if (variable_name)
			free(variable_name);
		return (-1);
	}
	variable_name = modify_variable(variable_name);
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
char	*expand_and_replace_vars(char *str, char ***envp_ptr, int exit_code)
{
	char	*result;
	char	*final_str;
	int		i;
	int		j;
	char	*exit_str;
	char	*pid_str;
	char	*var_name;
	int		env_index;
	char	*var_value;

	result = ft_calloc(ft_strlen(str) * 2 + 20, sizeof(char));
	if (!result)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				exit_str = ft_itoa(exit_code);
				ft_strlcat(result, exit_str, ft_strlen(result)
					+ ft_strlen(exit_str) + 1);
				j += ft_strlen(exit_str);
				free(exit_str);
				i += 2;
			}
			else if (str[i + 1] == '$')
			{
				pid_str = ft_itoa(getpid());
				ft_strlcat(result, pid_str, ft_strlen(result)
					+ ft_strlen(pid_str) + 1);
				j += ft_strlen(pid_str);
				free(pid_str);
				i += 2;
			}
			else
			{
				var_name = detect_varaible_name(&str[i]);
				if (var_name && ft_strlen(var_name) > 0)
				{
					env_index = check_on_evnp(ft_strdup(var_name), *envp_ptr);
					if (env_index >= 0)
					{
						var_value = get_variable_value(env_index, *envp_ptr);
						ft_strlcat(result, var_value, ft_strlen(result)
							+ ft_strlen(var_value) + 1);
						j += ft_strlen(var_value);
					}
					i += ft_strlen(var_name) + 1;
					free(var_name);
				}
				else
				{
					result[j++] = str[i++];
					if (var_name)
						free(var_name);
				}
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	final_str = ft_strdup(result);
	free(result);
	return (final_str);
}

static int	process_n_flags(char **argv, int *i)
{
	int	j;
	int	new_line;

	new_line = 1;
	j = 1;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		j = 1;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != '\0')
			break ;
		new_line = 0;
		(*i)++;
	}
	return (new_line);
}

int	ft_echo(char **argv, char ***envp_ptr, int exit_code)
{
	int		i;
	int		new_line;
	char	*str;

	i = 1;
	new_line = process_n_flags(argv, &i);
	while (argv[i] != NULL)
	{
		str = process_arguments(argv[i]);
		if (!is_single_quoted(argv[i]))
			str = expand_and_replace_vars(str, envp_ptr, exit_code);
		if (str)
		{
			write(STDOUT_FILENO, str, ft_strlen(str));
			free(str);
		}
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
