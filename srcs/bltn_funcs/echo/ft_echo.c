/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:08 by kadferna          #+#    #+#             */
/*   Updated: 2025/08/21 22:16:11 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*process_arguments(char *str)
{
	char	*processed_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	processed_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!processed_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == 39) && (i == 0
				|| i == (int)ft_strlen(str) - 1))
		{
			i++;
			continue ;
		}
		processed_str[j] = str[i];
		j++;
		i++;
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

char	*check_variables(char *str, char ***envp_ptr)
{
	char	*varaible_name;
	char	*value;
	int		i;

	varaible_name = detect_varaible_name(str);
	if (!varaible_name)
		return (NULL);
	i = check_on_evnp(str, *envp_ptr);
	if (i < 0)
		value = NULL;
	else
		value = get_variable_value(i, *envp_ptr);
	return (value);
}

int	ft_echo(char **argv, char ***envp_ptr)
{
	int		i;
	int		new_line;
	char	*str;

	i = 1;
	new_line = 1;
	if (argv[i] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i] != NULL)
	{
		str = process_arguments(argv[i]);
		str = check_variables(str, envp_ptr);
		if (str)
			write(STDOUT_FILENO, str, ft_strlen(str));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		free(str);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
