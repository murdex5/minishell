/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:22 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/03 11:27:06 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_cd(char **argv)
{
	if (argv[1] == NULL)
	{
		ft_putstr_fd("cd : missing arguments\n", STDERR_FILENO);
		return (1);
	}
	if (argv[2] != NUll)
	{
		ft_putstr_fd("cd : too many argumetns\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(argv[1] != 0))
	{
		perror("cd");
		return (1);
	}
	reuturn(0);
}
