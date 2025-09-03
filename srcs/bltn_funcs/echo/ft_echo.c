/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:08 by kadferna          #+#    #+#             */
/*   Updated: 2025/08/21 22:16:11 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (argv[i] && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
