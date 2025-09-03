/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:22:02 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/23 13:22:04 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**construct_tokens(char *line)
{
	char		**tokens;
	int			word_count;
	int			i;
	const char	*line_ptr;

	if (!line)
		return (NULL);
	line_ptr = line;
	word_count = count_words_shell(line_ptr);
	tokens = malloc(sizeof(char *) * (word_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	line_ptr = line;
	while (i < word_count)
	{
		tokens[i] = get_next_word(&line_ptr);
		if (!tokens[i])
			return (free_on_error(tokens, i), NULL);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

t_token	*get_tokens(char **tokens)
{
	t_token	*token;
	t_token	*current;
	int		i;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	i = 0;
	current = token;
	while (tokens[i] != NULL)
	{
		current->value = tokens[i];
		if (tokens[i + 1] != NULL)
		{
			current->next = malloc(sizeof(t_token));
			if (!current->next)
				return (free_on_exiting_list(token), NULL);
			current = current->next;
		}
		else
			current->next = NULL;
		i++;
	}
	specify_tokens(token);
	return (token);
}

t_token	*init_tokens(char *line)
{
	char **tokens;
	t_token *token;

	tokens = construct_tokens(line);
	if (!tokens)
		return (NULL);
	token = get_tokens(tokens);
	free(tokens);
	if (!token)
		return (NULL);
	return (token);
}
