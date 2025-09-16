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
	char	*env_var;
	char	*equal_pos;

	if (!envp_ptr || index < 0 || !envp_ptr[index])
		return (NULL);
	env_var = envp_ptr[index];
	equal_pos = ft_strchr(env_var, '=');
	if (!equal_pos || *(equal_pos + 1) == '\0')
		return (ft_strdup(""));
	return (ft_strdup(equal_pos + 1));
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

char	*detect_varaible_name(char *str)
{
	int		start;
	int		end;
	char	*var_name;

	if (str[0] != '$' || !str[1])
		return (NULL);
	start = 1;
	if (!ft_isalpha(str[start]) && str[start] != '_')
		return (NULL);
	end = start + 1;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	var_name = malloc(end - start + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + start, end - start + 1);
	return (var_name);
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

int	append_str(char *dest, int start_index, const char *src)
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
