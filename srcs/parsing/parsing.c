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

	type = get_redir_type((*token)->type);
	advance_token(token); // Consume redirection token (e.g., '<')
	
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (NULL);
	}
	
	redir = create_redirect(type, (*token)->value);
	advance_token(token); // Consume filename token
	return (redir);
}

t_ast_node	*parse_cmds(t_token **token)
{
	t_command_node	*cmd;
	t_list			*words;
	t_redirect		*redirs;
	t_redirect		*new_redir;

	words = NULL;
	redirs = NULL;
	cmd = malloc(sizeof(t_command_node));
	if (!cmd) return (NULL);
	cmd->type = NODE_COMMAND;
	cmd->argv = NULL;
	cmd->redirections = NULL;

	// A simple command is a sequence of tokens terminated by a pipe or the end.
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redirection(*token))
		{
			new_redir = parse_redirections(token);
			if (!new_redir)
			{
				ft_lstclear(&words, free);
				free_redirects(redirs);
				free(cmd);
				return (NULL);
			}
			add_redirect(&redirs, new_redir);
		}
		else if ((*token)->type == TOKEN_WORD)
		{
			ft_lstadd_back(&words, ft_lstnew(ft_strdup((*token)->value)));
			advance_token(token);
		}
		else // If it's not a redir, not a word, and not a pipe, it's a syntax error.
		{
			ft_putstr_fd("minishell: syntax error: unexpected token\n", 2);
			ft_lstclear(&words, free);
			free_redirects(redirs);
			free(cmd);
			return (NULL);
		}
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
		if (!*token) { // Dangling pipe
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
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
	t_token		*current = token;
	t_ast_node	*ast;

	if (!current)
		return (NULL);

	ast = parse_pipe(&current);

	if (current != NULL) // Leftover tokens mean a syntax error
	{
		ft_putstr_fd("minishell: syntax error: unexpected token at end of command\n", 2);
		free_ast(ast);
		// Do not free tokens here; the caller of parse() is responsible for them
		return (NULL);
	}
	return (ast);
}
