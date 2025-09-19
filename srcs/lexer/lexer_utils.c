/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:15:22 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/19 16:45:52 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == '<' || c == '>' || c == '|');
}

int	count_words_shell(const char *s)
{
	int		i;
	int		count;
	char	quote_state;

	i = 0;
	count = 0;
	quote_state = 0;
	while (s[i])
	{
		skip_whitespace(s, &i);
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			count += count_redir_or_pipe(s, &i);
		else if (s[i])
			count += count_word_token(s, &i, &quote_state);
	}
	return (count);
}

char	*get_next_word(const char **s)
{
	int		i;
	char	*word;

	i = 0;
	skip_whitespace(*s, &i);
	word = handle_redir_pipe(*s, &i);
	if (word)
	{
		*s += i;
		return (word);
	}
	word = extract_word_token(*s, &i);
	*s += i;
	return (word);
}

void	specify_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, "|", 2) == 0)
			current->type = TOKEN_PIPE;
		else if (ft_strncmp(current->value, "<", 2) == 0)
			current->type = TOKEN_REDIR_IN;
		else if (ft_strncmp(current->value, ">", 2) == 0)
			current->type = TOKEN_REDIR_OUT;
		else if (ft_strncmp(current->value, "<<", 3) == 0)
			current->type = TOKEN_HEREDOC;
		else if (ft_strncmp(current->value, ">>", 3) == 0)
			current->type = TOKEN_REDIR_APPEND;
		else
			current->type = TOKEN_WORD;
		current = current->next;
	}
}

t_token	*handle_new(t_token *head, int i, char **tokens)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (free_token(head), NULL);
	new->value = ft_strdup(tokens[i]);
	if (!new->value)
		return (free(new), free_token(head), NULL);
	new->next = NULL;
	new->type = TOKEN_WORD;
	return (new);
}
