/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:40:07 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/28 11:40:08 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirect	*create_redirect(t_redirect_type type, char *filename)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->type = type;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	return (new);
}

void	add_redirect(t_redirect **list, t_redirect *new)
{
	t_redirect *curr;

	if (!*list)
	{
		*list = new;
		return ;
	}
	curr = *list;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
