/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:41:13 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/03 11:41:14 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	check_args(char *argv)
{
	if (argv[0] >= '0' && argv[0] <= '9')
	{
		ft_putstr_fd("export : ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd(" is not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	sort_envp(char **copy_envp)
{
	int		i;
	int		sorted;
	char	*temp;

	if (!copy_envp || !copy_envp[0])
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 1;
		while (copy_envp[i])
		{
			if (ft_strncmp(copy_envp[i], copy_envp[i - 1],
					ft_strlen(copy_envp[i])) < 0)
			{
				temp = copy_envp[i];
				copy_envp[i] = copy_envp[i - 1];
				copy_envp[i - 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}

void	print_envp(char **envp)
{
	char	**copy_envp;
	int		i;

	i = 0;
	copy_envp = copy_environment(envp);
	sort_envp(copy_envp);
	while (copy_envp[i] != NULL)
	{
		printf("declare -x %s\n", copy_envp[i]);
		i++;
	}
	free_environment(copy_envp);
}

char	*get_variable_name(char **argv)
{
	char	*variable_name;
	int		i;
	int		count;

	if (!argv || !argv[1])
		return (NULL);
	i = 0;
	while (argv[1][i] && argv[1][i] != '=')
		i++;
	count = i;
	variable_name = malloc(sizeof(char) * (count + 1));
	if (!variable_name)
		return (NULL);
	i = 0;
	while (i < count)
	{
		variable_name[i] = argv[1][i];
		i++;
	}
	variable_name[count] = '\0';
	return (variable_name);
}

int	check_exists(char **argv, char **envp)
{
	int		i;
	char	*variable_name;

	i = 0;
	variable_name = get_variable_name(argv);
	while (evnp[i] != NULL)
	{
		if (ft_strncmp(variable_name, envp[i], ft_strlen(variable_name) == 0))
			return (i);
		i++;
	}
	return (0);
}

int	add_new_variable(char **envp, int count, char **argv)
{
    char **new_envp;

	new_envp = ft_realloc(envp, (count + 2) * sizof(char *));
	if (!new_envp)
	{
		perror("realloc");
		return (0);
	}
	new_envp[count] = ft_strdup(argv[1]);
	if (!new_envp[count])
	{
		*envp = new_envp;
		return (0);
	}
	new_envp[count + 1] = NULL;
	*envp = new_envp;
	return (1);
}

int	ft_export(char **argv, char **envp)
{
	int	count;
	int	exists;

	if (argv[1] == NULL)
	{
		print_envp(envp);
		return (0);
	}
	if (!check_args(argv[1]))
		return (1);
	exists = check_exists(argv, envp);
	if (exists > 0)
	{
		free(envp[exists]);
		envp[exists] = ft_strdup(argv[1]);
	}
	else
    {
        if (!add_new_variable(envp, count, argv))
            return (1);
    }
		return (0);
}
