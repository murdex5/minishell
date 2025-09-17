/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:34 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/16 16:50:38 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirect	*parse_redirections(t_token **token)
{
	t_redirect		*redir;
	t_redirect_type	type;

	if (!token || !*token)
		return (NULL);
	type = get_redir_type((*token)->type);
	if (type == REDIR_NONE)
		return (NULL);
	advance_token(token);
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putstr_fd("Syntax error: missing filename\n", 2);
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
	cmd = malloc(sizeof(t_command_node));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_COMMAND;
	while (*token && ((*token)->type == TOKEN_WORD || is_redirection(*token)))
	{
		if ((*token)->type == TOKEN_WORD)
		{
			ft_lstadd_back(&words, ft_lstnew(ft_strdup((*token)->value)));
			advance_token(token);
		}
		else
			add_redirect(&redirs, parse_redirections(token));
	}
	cmd->argv = list_to_array(words);
	cmd->redirections = redirs;
	ft_lstclear(&words, free);
	return ((t_ast_node *)cmd);
}

t_ast_node	*parse_pipe(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_pipe_node	*pipe_node;

	left = parse_cmds(token);
	if (!left)
		return (NULL);
	while (*token && (*token)->type == TOKEN_PIPE)
	{
		advance_token(token);
		right = parse_cmds(token);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		pipe_node = create_pipe_node(left, right);
		if (!pipe_node)
			return (free_ast(left), free_ast(right), NULL);
		left = (t_ast_node *)pipe_node;
	}
	return (left);
}

t_ast_node	*parse(t_token *token)
{
	t_token		*current;
	t_ast_node	*ast;

	current = token;
	ast = parse_pipe(&current);
	if (!ast)
		return (NULL);
	if (current && current->type != TOKEN_EOF)
	{
		ft_putstr_fd("Syntax error: unexpected token\n", 2);
		free_token(token);
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
