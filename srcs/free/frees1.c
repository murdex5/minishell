/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:30:24 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/16 22:30:27 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_environment(char **msh_envp)
{
	int	i;

	if (!msh_envp)
		return ;
	i = 0;
	while (msh_envp[i])
	{
		free(msh_envp[i]);
		i++;
	}
	free(msh_envp);
}

void	free_tokens_array(char **tokens)
{
	int	i;

	if ((!tokens) || !(*tokens))
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_on_exiting_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->value != NULL)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	free_pipe(t_ast_node *node)
{
	t_pipe_node	*pipe;

	pipe = (t_pipe_node *)node;
	if (pipe->left)
	{
		free_ast(pipe->left);
		pipe->left = NULL;
	}
	if (pipe->right)
	{
		free_ast(pipe->right);
		pipe->right = NULL;
	}
	free(pipe);
}
