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

static int	append_str(char *dest, int start_index, const char *src)
{
	int	k;

	k = 0;
	if (!src)
		return (0);
	while (src[k])
	{
		dest[start_index + k] = src[k];
		k++;
	}
	return (k);
}

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
	char	*modified_name;

	if (!variable_name || *variable_name == '\0')
		return (-1);
	modified_name = ft_strdup(variable_name);
	len = ft_strlen(modified_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(modified_name, envp[i], len) == 0 && (envp[i][len] == '='
				|| envp[i][len] == '\0'))
		{
			free(modified_name);
			return (i);
		}
		i++;
	}
	free(modified_name);
	return (-1);
}

char	*expand_and_replace_vars(char *str, char ***envp_ptr, int exit_code)
{
	char	*result;
	char	*final_str;
	int		i;
	int		j;
	char	*var_name;
	int		env_index;
	char	*exit_str;
	char	*pid_str;
	char	*var_value;

	result = ft_calloc(ft_strlen(str) * 4 + 20, sizeof(char));
	if (!result)
		return (ft_strdup(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				exit_str = ft_itoa(exit_code);
				j += append_str(result, j, exit_str);
				free(exit_str);
				i += 2;
			}
			else if (str[i + 1] == '$')
			{
				pid_str = ft_itoa(getpid());
				j += append_str(result, j, pid_str);
				free(pid_str);
				i += 2;
			}
			else
			{
				var_name = detect_varaible_name(&str[i]);
				if (var_name && ft_strlen(var_name) > 0)
				{
					env_index = check_on_evnp(var_name, *envp_ptr);
					if (env_index >= 0)
					{
						var_value = get_variable_value(env_index, *envp_ptr);
						j += append_str(result, j, var_value);
						free(var_value);
					}
					i += ft_strlen(var_name) + 1; // +1 for the '$'
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

int	ft_echo(char **argv)
{
	int		i;
	int		new_line;
	char	*str;

	i = 1;
	new_line = process_n_flags(argv, &i);
	while (argv[i] != NULL)
	{
		str = process_arguments(argv[i]);
		;
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
