/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:16:56 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/17 11:17:01 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_ast(t_ast_node *node)
{
	int				i;
	t_command_node	*cmd;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		cmd = (t_command_node *)node;
		if (cmd->argv)
		{
			i = -1;
			while (cmd->argv[++i])
			{
				free(cmd->argv[i]);
				cmd->argv[i] = NULL;
			}
			free(cmd->argv);
			cmd->argv = NULL;
		}
		free_redirects(cmd->redirections);
		cmd->redirections = NULL;
		free(cmd);
	}
	else if (node->type == NODE_PIPE)
		free_pipe(node);
}

void	free_til(char **tokens, int i)
{
	if ((!tokens) || !(*tokens))
		return ;
	while (i > 0)
	{
		i--;
		free(tokens[i]);
	}
	free(tokens);
}
