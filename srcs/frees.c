/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:31:48 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/14 10:31:50 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_r1(char *r1)
{
	if (r1 == NULL)
		return ;
	free(r1);
}

int	free_on_error(char **result, int word_count)
{
	while (word_count > 0)
	{
		word_count--;
		free(result[word_count]);
	}
	return (0);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free(node);
}

void	free_on_exiting_list(t_token *tokens)
{
	t_token *current;
	t_token *next;

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

void	free_environment(char **msh_envp)
{
	int	i;

	if (!msh_envp)
		return;
	i = 0;
	while (msh_envp[i])
	{
		free(msh_envp[i]);
		i++;
	}
	free(msh_envp);
}
