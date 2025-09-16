/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:14:42 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/31 11:14:44 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	advance_token(t_token **token)
{
	if (*token && (*token)->next)
		*token = (*token)->next;
	else
		*token = NULL;
}

t_pipe_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_pipe_node	*node;

	node = malloc(sizeof(t_pipe_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	return (node);
}

t_redirect_type	get_redir_type(t_tokentype token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_NONE);
}

bool	is_redirection(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC);
}

int	put_content(t_list *tmp, char **array, int *i)
{
	while (tmp)
	{
		array[*i] = ft_strdup((char *)tmp->content);
		if (!array[*i])
		{
			while (*i > 0)
			{
				(*i)--;
				free(array[*i]);
			}
			return (0);
		}
		(*i)++;
		tmp = tmp->next;
	}
	return (1);
}
