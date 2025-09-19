/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:40:41 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/20 00:41:03 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	modulo_val(int exit_code)
{
	int	mod_val;

	mod_val = exit_code % 256;
	return (mod_val);
}

int	argv_list_len(char **argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}
