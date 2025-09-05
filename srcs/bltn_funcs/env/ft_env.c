/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:41:25 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/05 12:41:27 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_env(char **envp_ptr)
{
	int	i;

	i = 0;
	if (!envp_ptr || !*envp_ptr)
		return (1);
	while (envp_ptr[i] != NULL)
	{
		ft_putstr_fd(envp_ptr[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
