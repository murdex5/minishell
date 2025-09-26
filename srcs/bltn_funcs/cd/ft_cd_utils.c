/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:53:11 by anjbaiju          #+#    #+#             */
/*   Updated: 2025/09/24 14:54:01 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*handle_home_dash(char *arg, char **envp)
{
	char	*target_dir;

	target_dir = NULL;
	if (arg == NULL || ft_strcmp(arg, "~") == 0)
	{
		target_dir = get_env_value("HOME", envp);
		if (!target_dir)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		target_dir = get_env_value("OLDPWD", envp);
		if (!target_dir)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		else
		{
			ft_putstr_fd(target_dir, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	return (target_dir);
}

char	*resolve_target_dir(char **argv, char **envp)
{
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0 || ft_strcmp(argv[1],
			"-") == 0)
		return (handle_home_dash(argv[1], envp));
	else if (argv[2] != NULL)
	{
		ft_putstr_fd("cd : too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	else
		return (argv[1]);
}

int	change_directory(char *target_dir, char **envp, char *old_pwd)
{
	char	new_pwd[PATH_MAX];

	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(target_dir, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (perror("pwd"), 1);
	update_env_var(&envp, "OLDPWD", old_pwd);
	update_env_var(&envp, "PWD", new_pwd);
	return (0);
}
