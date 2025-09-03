/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:01:39 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/31 12:01:41 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirect	*create_redirect_node(t_redirect_type type, char *filename)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->type = type;
	new->filename = strdup(filename);
	new->next = NULL;
	return (new);
}

char	**list_to_array(t_list *lst)
{
	char	**array;
	int		len;
	int		i;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	len = 0;
	tmp = lst;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = lst;
	if (!put_content(tmp, array, &i))
		return (NULL);
	array[i] = NULL;
	return (array);
}
