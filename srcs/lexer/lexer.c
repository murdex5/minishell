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
			return (free_til(tokens, i), NULL);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

t_token	*get_tokens(char **tokens)
{
	t_token	*head;
	t_token	*current;
	t_token	*new;
	int		i;

	if (!tokens || !tokens[0])
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (tokens[i] != NULL)
	{
		new = handle_new(head, i, tokens);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	specify_tokens(head);
	return (head);
}

t_token	*init_tokens(char *line)
{
	char	**tokens;
	t_token	*token;
	int		i;

	tokens = construct_tokens(line);
	if (!tokens)
		return (NULL);
	token = get_tokens(tokens);
	if (tokens)
	{
		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
	if (!token)
		return (NULL);
	return (token);
}
