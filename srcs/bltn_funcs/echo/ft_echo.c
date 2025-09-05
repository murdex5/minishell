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

char	*process_arguments(char *str)
{
	char	*processed_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	processed_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!processed_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == 39) && (i == 0
				|| i == (int)ft_strlen(str) - 1))
		{
			i++;
			continue ;
		}
		processed_str[j] = str[i];
		j++;
		i++;
	}
	processed_str[j] = '\0';
	return (processed_str);
}

int	ft_echo(char **argv)
{
	int		i;
	int		new_line;
	char	*str;

	i = 1;
	new_line = 1;
	if (argv[i] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i] != NULL)
	{
		str = process_arguments(argv[i]);
		write(STDOUT_FILENO, str, ft_strlen(str));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		free(str);
		str = NULL;
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
