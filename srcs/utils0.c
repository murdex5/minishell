/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:34 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/10 14:41:48 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char *r1, t_token *token, char **envp_ptr, t_ast_node *pipe)
{
	printf("exit\n");
	if (envp_ptr != NULL)
		free_environment(envp_ptr);
	if (token)
		free_token(token);
	if (pipe)
		free_ast(pipe);
	if (r1)
		free(r1);
}

int	is_single_quoted(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' && str[strlen(str) - 1] == '\'')
		return (1);
	return (0);
}

void	*ft_realloc(void *a, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!new_size)
	{
		free(a);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (a)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, a, copy_size);
		free(a);
	}
	return (new_ptr);
}

int	get_array_len(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (i);
	while (tokens[i] != NULL)
		i++;
	return (i);
}
