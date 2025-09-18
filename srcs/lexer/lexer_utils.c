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
		|| c == '\r' || c == '<' || c == '>' || c == '|');
}

int	count_words_shell(const char *s)
{
	int		count;
	char	quote_state;
	int		i;

	count = 0;
	quote_state = 0;
	i = 0;
	while (s[i])
	{
		// Skip spaces
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
				|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r'))
			i++;
		// Check for redirection operators (<<, >>, <, >)
		if (s[i] == '<' || s[i] == '>')
		{
			count++;                          // Count this operator as a token
			if (s[i + 1] && s[i + 1] == s[i]) // Check for << or >>
				i++;
			i++;
			continue ;
		}
		// Check for pipe
		else if (s[i] == '|')
		{
			count++;
			i++;
			continue ;
		}
		// Normal word token
		else if (s[i])
		{
			count++;
			// Process the word, handling quotes
			while (s[i] && ((s[i] != ' ' && s[i] != '\t' && s[i] != '\n'
						&& s[i] != '\v' && s[i] != '\f' && s[i] != '\r'
						&& s[i] != '<' && s[i] != '>' && s[i] != '|')
					|| quote_state))
			{
				if (!quote_state && (s[i] == '\'' || s[i] == '"'))
					quote_state = s[i];
				else if (quote_state == s[i])
					quote_state = 0;
				i++;
			}
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
	// Skip spaces
	while (**s && (**s == ' ' || **s == '\t' || **s == '\n' || **s == '\v'
			|| **s == '\f' || **s == '\r'))
		(*s)++;
	// Handle redirection operators
	if (**s == '<' || **s == '>')
	{
		start = *s;
		len = 1;
		// Check for << or >>
		if ((*s)[1] && (*s)[1] == **s)
			len = 2;
		word = malloc(sizeof(char) * (len + 1));
		if (!word)
			return (NULL);
		ft_strlcpy(word, start, len + 1);
		*s += len;
		return (word);
	}
	// Handle pipe
	else if (**s == '|')
	{
		word = malloc(sizeof(char) * 2);
		if (!word)
			return (NULL);
		word[0] = '|';
		word[1] = '\0';
		(*s)++;
		return (word);
	}
	// Normal word token
	else
	{
		start = *s;
		len = 0;
		while ((*s)[len] && (((*s)[len] != ' ' && (*s)[len] != '\t'
					&& (*s)[len] != '\n' && (*s)[len] != '\v'
					&& (*s)[len] != '\f' && (*s)[len] != '\r'
					&& (*s)[len] != '<' && (*s)[len] != '>' && (*s)[len] != '|')
				|| quote_state))
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
