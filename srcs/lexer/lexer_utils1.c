/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:46:06 by anjbaiju          #+#    #+#             */
/*   Updated: 2025/09/19 16:49:46 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_whitespace(const char *s, int *i)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n'
			|| s[*i] == '\v' || s[*i] == '\f' || s[*i] == '\r'))
		(*i)++;
}

int	count_redir_or_pipe(const char *s, int *i)
{
	int	c;

	c = 0;
	if (s[*i] == '<' || s[*i] == '>')
	{
		c++;
		if (s[*i + 1] && s[*i + 1] == s[*i])
			(*i)++;
		(*i)++;
	}
	else if (s[*i] == '|')
	{
		c++;
		(*i)++;
	}
	return (c);
}

char	*handle_redir_pipe(const char *s, int *i)
{
	const char	*start = s + *i;
	int			len;
	char		*word;

	len = 1;
	if (s[*i] == '<' || s[*i] == '>')
	{
		if (s[*i + 1] && s[*i + 1] == s[*i])
			len = 2;
	}
	else if (s[*i] == '|')
		len = 1;
	else
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	*i += len;
	return (word);
}

int	count_word_token(const char *s, int *i, char *quote)
{
	int	started;

	started = 0;
	if (s[*i])
	{
		started = 1;
		while (s[*i] && ((s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\n'
					&& s[*i] != '\v' && s[*i] != '\f' && s[*i] != '\r'
					&& s[*i] != '<' && s[*i] != '>' && s[*i] != '|') || *quote))
		{
			if (!*quote && (s[*i] == '\'' || s[*i] == '"'))
				*quote = s[*i];
			else if (*quote == s[*i])
				*quote = 0;
			(*i)++;
		}
	}
	return (started);
}

char	*extract_word_token(const char *s, int *i)
{
	const char	*start = s + *i;
	int			len;
	char		quote;
	char		*word;

	len = 0;
	quote = 0;
	while (s[*i] && ((!is_separator(s[*i])) || quote))
	{
		if (!quote && (s[*i] == '\'' || s[*i] == '"'))
			quote = s[*i];
		else if (quote == s[*i])
			quote = 0;
		(*i)++;
		len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}
