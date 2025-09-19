/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:34 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/20 00:10:03 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirect	*parse_redirections(t_token **token)
{
	t_redirect		*redir;
	t_redirect_type	type;

	type = get_redir_type((*token)->type);
	advance_token(token);
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (NULL);
	}
	redir = create_redirect(type, (*token)->value);
	advance_token(token);
	return (redir);
}

t_ast_node	*parse_cmds(t_token **token)
{
	t_command_node	*cmd;
	t_list			*words;
	t_redirect		*redirs;

	words = NULL;
	redirs = NULL;
	cmd = init_command_node();
	if (!cmd)
		return (NULL);
	if (!process_command_tokens(token, &words, &redirs))
	{
		free(cmd);
		return (NULL);
	}
	if (words)
	{
		cmd->argv = list_to_array(words);
		ft_lstclear(&words, free);
	}
	cmd->redirections = redirs;
	return ((t_ast_node *)cmd);
}

t_ast_node	*parse_pipe(t_token **token)
{
	t_ast_node	*node;
	t_ast_node	*right;

	node = parse_cmds(token);
	if (!node)
		return (NULL);
	while (*token && (*token)->type == TOKEN_PIPE)
	{
		advance_token(token);
		if (!*token)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
			free_ast(node);
			return (NULL);
		}
		right = parse_cmds(token);
		if (!right)
		{
			free_ast(node);
			return (NULL);
		}
		node = (t_ast_node *)create_pipe_node(node, right);
	}
	return (node);
}

t_ast_node	*parse(t_token *token)
{
	t_token		*current;
	t_ast_node	*ast;

	current = token;
	if (!current)
		return (NULL);
	ast = parse_pipe(&current);
	if (current != NULL)
	{
		ft_putstr_fd("minishell: syntax error: ", 2);
		ft_putstr_fd("unexpected token at end of command\n", 2);
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
