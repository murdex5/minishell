/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:31:34 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/09 15:40:56 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_variable_value(int index, char **envp_ptr)
{
	char	*value;
	int		j;
	int		i;

	i = 0;
	while (envp_ptr[index][i] != '=')
		i++;
	i++;
	j = (int)ft_strlen(envp_ptr[i]) - i;
	value = malloc(sizeof(char) * j + 1);
	j = 0;
	while (envp_ptr[index][i] != '\0')
	{
		value[j] = envp_ptr[index][i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

char	*modify_variable(char *str)
{
	int		i;
	int		j;
	char	*modified_str;

	if ((int)ft_strlen(str) < 0)
		return (NULL);
	i = 1;
	j = 0;
	modified_str = malloc(sizeof(char) * ft_strlen(str));
	if (!modified_str)
		return (NULL);
	while (str[i] != '\0')
	{
		modified_str[j] = str[i];
		i++;
		j++;
	}
	modified_str[j] = '\0';
	return (modified_str);
}

char	*detect_varaible_name(char *argv)
{
	int		i;
	char	**strs;
	char	*varaible_name;

	strs = ft_split(argv, ' ');
	varaible_name = NULL;
	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
	{
		if (strs[i][0] == '$')
		{
			varaible_name = ft_strdup(strs[i]);
			free_tokens(strs);
			if (!varaible_name)
				return (NULL);
			return (varaible_name);
		}
		i++;
	}
	free_tokens(strs);
	return (NULL);
}

int	validate_quotes(const char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (str[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		write(2, "minishell: syntax error: unmatched quote\n", 41);
		return (0);
	}
	return (1);
}
