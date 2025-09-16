/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:08 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/15 09:58:30 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*process_arguments(const char *str)
{
	char	*processed_str;
	char	quote;

	quote = 0;
	processed_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!processed_str)
		return (NULL);
	find_quote(str, processed_str, quote);
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
	char			*result;
	char			*final_str;
	int				i;
	t_expand_data	data;

	result = ft_calloc(ft_strlen(str) * 4 + 20, sizeof(char));
	if (!result)
		return (ft_strdup(str));
	data.result = result;
	data.envp_ptr = envp_ptr;
	data.exit_code = exit_code;
	data.j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			data.j = process_dollar_sign(str, &i, &data);
		else
			data.result[data.j++] = str[i++];
	}
	data.result[data.j] = '\0';
	final_str = ft_strdup(data.result);
	free(data.result);
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
