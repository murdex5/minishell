/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:36:48 by anjbaiju          #+#    #+#             */
/*   Updated: 2025/09/19 16:36:49 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command_node	*init_command_node(void)
{
	t_command_node	*cmd;

	cmd = malloc(sizeof(t_command_node));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_COMMAND;
	cmd->argv = NULL;
	cmd->redirections = NULL;
	return (cmd);
}

bool	handle_redirection(t_token **token, t_list **words, t_redirect **redirs)
{
	t_redirect	*new_redir;

	new_redir = parse_redirections(token);
	if (!new_redir)
	{
		ft_lstclear(words, free);
		free_redirects(*redirs);
		return (false);
	}
	add_redirect(redirs, new_redir);
	return (true);
}

bool	process_command_tokens(t_token **token, t_list **words,
		t_redirect **redirs)
{
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redirection(*token))
		{
			if (!handle_redirection(token, words, redirs))
				return (false);
		}
		else if ((*token)->type == TOKEN_WORD)
		{
			ft_lstadd_back(words, ft_lstnew(ft_strdup((*token)->value)));
			advance_token(token);
		}
		else
		{
			ft_putstr_fd("minishell: syntax error: unexpected token\n", 2);
			ft_lstclear(words, free);
			free_redirects(*redirs);
			return (false);
		}
	}
	return (true);
}
