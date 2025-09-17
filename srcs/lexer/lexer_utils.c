/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:15:22 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/28 11:15:26 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	count_words_shell(const char *s)
{
	int		count;
	char	quote_state;

	count = 0;
	quote_state = 0;
	while (*s)
	{
		while (*s && is_separator(*s))
			s++;
		if (*s)
			count++;
		while (*s && (!is_separator(*s) || quote_state))
		{
			if (!quote_state && (*s == '\'' || *s == '"'))
				quote_state = *s;
			else if (quote_state == *s)
				quote_state = 0;
			s++;
		}
	}
	return (count);
}

char	*get_next_word(const char **s)
{
	char		quote_state;
	const char	*start;
	int			len;
	char		*word;

	quote_state = 0;
	len = 0;
	while (**s && is_separator(**s))
		(*s)++;
	start = *s;
	while ((*s)[len] && (!is_separator((*s)[len]) || quote_state))
	{
		if (!quote_state && ((*s)[len] == '\'' || (*s)[len] == '"'))
			quote_state = (*s)[len];
		else if (quote_state == (*s)[len])
			quote_state = 0;
		len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	*s += len;
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
