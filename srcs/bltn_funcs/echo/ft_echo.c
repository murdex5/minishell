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
	if (argv[i] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i] != NULL)
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
