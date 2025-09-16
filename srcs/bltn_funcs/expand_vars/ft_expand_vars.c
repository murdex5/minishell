/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:15:57 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/15 10:15:59 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	result = ft_substr(str, 1, len - 2);
	return (result);
}

char	*expand_and_process_arguemetns(char *curr_str, char ***envp_ptr,
		int exit)
{
	char	*temp_str;
	char	*mod_str;

	temp_str = process_arguments(curr_str);
	if (!temp_str)
		return (NULL);
	mod_str = expand_and_replace_vars(temp_str, envp_ptr, exit);
	if (temp_str)
		free(temp_str);
	return (mod_str);
}

static void	replace_given_val(t_token *current)
{
	free(current->value);
	current->value = ft_strdup("");
}

void	expand_token_variables(t_token *tokens, int exit, char ***envp_ptr)
{
	t_token	*current;
	char	*mod_str;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value)
		{
			if (is_single_quoted(current->value))
				mod_str = remove_quotes(current->value);
			else
				mod_str = expand_and_process_arguemetns(current->value,
						envp_ptr, exit);
			if (mod_str)
			{
				free(current->value);
				current->value = mod_str;
			}
			else
				replace_given_val(current);
		}
		current = current->next;
	}
}
